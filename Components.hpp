
struct PositionComponent
{
    float x;
    float y;
    float z;
};

struct CameraComponent
{
    float tarX;
    float tarY;
    float tarZ;
};

struct SoundComponent
{
    std::string event_id;
    std::map<std::string, float> floatparameers;
    std::map<std::string, int> intParameters;
    uint8_t marked_for_parameter_update;
    uint8_t marked_for_stop;
    uint8_t marked_for_play;
};

struct ListenerComponent
{};

