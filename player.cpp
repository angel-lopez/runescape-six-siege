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

  void move(double time);
};

Player::Player() {}
Player::~Player() {}

void Player::move(double time)
{
  coordinates.x += velocity.x * time;
  coordinates.y += velocity.y * time;
}