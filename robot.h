class Robot {
  private:
    int direction; // 0 -north, 1-east, etc.
    int locX;
    int locY;

  public:
    Robot();

    Robot(int direction, int locX, int locY);

    bool ray_casting();
}