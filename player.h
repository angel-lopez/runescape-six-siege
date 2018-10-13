class Player
{
public:
  struct
  {
    double x = 0;
    double y = 0;
  } coordinates;

  struct
  {
    int x = 0;
    int y = 0;
  } velocity;

  Player();
  ~Player();
};

Player::Player() {}

Player::~Player() {}
