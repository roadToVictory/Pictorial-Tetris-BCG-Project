#include "Play.h"
#include "Game.h"
#include "GameOver.h"
#include "Menu.h"

Play::Play() {
    Game& view = Game::getInstanceOfGame();
    if (Game::getInstanceOfGame().getWidthOfGameWindow() / Game::getInstanceOfGame().getHeightOfGameWindow()>16/9)
    {
        _leftBegin = Game::getInstanceOfGame().getWidthOfGameWindow() * 0.075f;
        _topBegin = Game::getInstanceOfGame().getHeightOfGameWindow() * 0.20f;
    }
    image = view.getTextureOfGivenImageNumber().copyToImage();
    sf::Image greyBackgroundImage = view.getTextureOfGivenImageNumber().copyToImage();

    for (unsigned int i = 0; i < greyBackgroundImage.getSize().y;++i)
        for (unsigned int j = 0; j < greyBackgroundImage.getSize().x;++j)
            greyBackgroundImage.setPixel(
                    j, i, convertColorToGrayscale(greyBackgroundImage.getPixel(j, i))
            );

    placePictureToBeAssembled(view);
    placeGrayPicture(view, greyBackgroundImage);
    cut();
}

void Play::eventListener(sf::Event &event) {
    Config& config = Game::getConfig();
    if (event.type == sf::Event::EventType::KeyPressed) {
        int ht;
        switch (event.key.code) {
            case sf::Keyboard::A:
            case sf::Keyboard::Left:
                _position--;
                if (_position < 0)_position++;
                 ht = config.getsetNumberOfBlocksPerPictureSide() - _stackHeight[_position] - 1;
                if (_current.getPosition().y >= _topBegin + _elementSiteLen * ht) {
                    _position++;
                }
                break;
            case sf::Keyboard::D:
            case sf::Keyboard::Right:
                _position++;
                if (_position > static_cast<int>(config.getsetNumberOfBlocksPerPictureSide()) - 1)_position--;
                ht = config.getsetNumberOfBlocksPerPictureSide() - _stackHeight[_position] - 1;
                if (_current.getPosition().y > _topBegin + _elementSiteLen * ht) {
                    _position--;
                }
                break;
            case sf::Keyboard::S:
            case sf::Keyboard::Down:
                _doubleSpeed = true;
                break;
            case sf::Keyboard::E:
                rotateBlockToRight();
                break;
            case sf::Keyboard::Q:
                rotateBlockToLeft();
                break;
            case sf::Keyboard::Escape:
                Game::getGameController().setNewGameLevel(std::make_unique<Menu>());
                break;
            default:
                break;

        }
    }
}

void Play::updateCurrentStateOfCurrentGameLevel(float dt) {
    Config& config = Game::getConfig();

    if (_isCurrentPlaced) {
        do {
            _currentColumn = rand() % config.getsetNumberOfBlocksPerPictureSide();
        } while(_unplaced[_currentColumn].empty());

        _current = _unplaced[_currentColumn].top();
        _position = config.getsetNumberOfBlocksPerPictureSide() / 2.0f;
        _current.setPosition(_leftBegin + _position * _elementSiteLen, - _elementSiteLen);
        _rotation = 0;
        for (int i = 0; i < rand() % 3 + 1;++i)
            rotateBlockToLeft();

        _isCurrentPlaced = false;
    }
    else {
        int ht = config.getsetNumberOfBlocksPerPictureSide() - _stackHeight[_position] - 1;
        double speed = _doubleSpeed ? 10 * config.getSpeedOfFallingBlocks() : config.getSpeedOfFallingBlocks();
        _current.setPosition(_leftBegin + _position * _elementSiteLen, _current.getPosition().y + speed * dt);

        if (_current.getPosition().y >= _topBegin + _elementSiteLen * ht&&
            _currentColumn == _position && _rotation == 0) {
            _current.setPosition(_leftBegin + _currentColumn * _elementSiteLen,
                                _topBegin + _elementSiteLen * ht);
            _placed.push_back(_current);
            _stackHeight[_currentColumn]++;
            _isCurrentPlaced = true;
            _doubleSpeed = false;
            _unplaced[_currentColumn].pop();
            if (_placed.size() == pow(config.getsetNumberOfBlocksPerPictureSide(), 2)) {
                Game::getGameController().setNewGameLevel(std::make_unique<GameOver>());
            }
        }
        else if (_current.getPosition().y >= _topBegin + _elementSiteLen * ht &&
                 (_currentColumn != _position || _rotation != 0)) {
             _isCurrentPlaced = true;
             _doubleSpeed = false;
        }
    }

    Game::getInstanceOfGame().gameTime += dt;
}

void Play::renderCurrentStateOfCurrentGameLevel() {
    sf::RenderTarget &target = Game::getInstanceOfGame().getRenderedWindow();
    target.clear(Game::getInstanceOfGame().getColorOfBackground());
    target.draw(_greyBackgroundSprite);
    target.draw(_rightSprite);
    target.draw(_current);

    for (auto it : _placed)
        target.draw(it);
}

sf::Color Play::convertColorToGrayscale(const sf::Color &color) {
    auto avg = static_cast<sf::Uint8>( color.r * 0.12f + color.g * 0.72f + color.b * 0.07f);
    return {avg, avg, avg};
}

sf::Sprite Play::getFragmentOfPicture(int i, int j) {
    double width = Game::getInstanceOfGame().getTextureOfGivenImageNumber().getSize().x;
    double height = Game::getInstanceOfGame().getTextureOfGivenImageNumber().getSize().y;
    double d = width < height ? width / Game::getConfig().getsetNumberOfBlocksPerPictureSide() : height / Game::getConfig().getsetNumberOfBlocksPerPictureSide();

    _elementSiteLen = d * _greyBackgroundSprite.getScale().x;

    int widthOffset=width>height ? (width - height) / 2 : 0, heightOffset= width < height ? (height - width)/2 :0;

    sf::Sprite sprite(Game::getInstanceOfGame().getTextureOfGivenImageNumber());
    sprite.setTextureRect(sf::IntRect(widthOffset + j * d, heightOffset + i * d, d, d));
    sprite.setScale(_greyBackgroundSprite.getScale());
    return sprite;
}

void Play::cut() {
    Config& config = Game::getConfig();
    _unplaced.resize(Game::getConfig().getsetNumberOfBlocksPerPictureSide());
    _stackHeight.resize(config.getsetNumberOfBlocksPerPictureSide());
    for (unsigned int i = 0; i < config.getsetNumberOfBlocksPerPictureSide();++i) {
        _stackHeight[i] = 0;
        for (unsigned int j = 0; j < config.getsetNumberOfBlocksPerPictureSide();++j)
            _unplaced[j].push(getFragmentOfPicture(i, j));
    }
}

void Play::rotateBlockToRight() {
    double origin = _elementSiteLen / _current.getScale().x;
    _current.rotate(90);
    _current.setOrigin(_rotation%3!=0?origin:0, _rotation > 1 ? 0 : origin);
    _rotation = (++ _rotation) % 4;

}

void Play::rotateBlockToLeft() {
    double origin = _elementSiteLen / _current.getScale().x;
    _current.rotate(-90);
    _current.setOrigin(_rotation % 3 != 0 ? 0 : origin, _rotation > 1 ? origin : 0);
    _rotation = _rotation-1 >= 0 ? _rotation-1: 3;
}

void Play::placePictureToBeAssembled(Game &view) {
    _rightTexture.loadFromImage(image);
    _rightSprite = view.transformTextureToSpriteWithResizing(_rightTexture, view.getWidthOfGameWindow() * 0.35f,
                              view.getWidthOfGameWindow() * 0.35f);
    _rightSprite.setPosition(view.getWidthOfGameWindow() * 0.5f + _leftBegin, _topBegin);
}

void Play::placeGrayPicture(Game &view, const sf::Image &greyBackgroundImage) {
    _greyBackgroundTexture.loadFromImage(greyBackgroundImage);

    _greyBackgroundSprite = view.transformTextureToSpriteWithResizing(_greyBackgroundTexture,
                                       view.getWidthOfGameWindow() * 0.35f,
                                       view.getWidthOfGameWindow() * 0.35f);
    _greyBackgroundSprite.setPosition(_leftBegin, _topBegin);
}
