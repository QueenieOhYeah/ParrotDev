/**
 *  Copyright (c) 2020 Parrot Drones SAS
 */
#pragma once

#include <Eigen/Eigen>

namespace physics
{
/**
 * @brief 6th order dynamic model for the horizontal motion.
 * @details Propagation model taking into account the drone horizontal dynamics
 *          and the horizontal controler.
 *          Model inputs reference are the targeted horizontal position, velocity and acceleration.
 *          Model outputs is an ideally modeled drone 6th dimension state vector
 *          Model response can be changed by tuning the gain vector
 */

class HorizontalIdealModel
{
public:
    enum State
    {
        /* Position Inputs */
        X = 0,
        Y,
        /* Velocity Inputs */
        DX,
        DY,
        /* Acceleration Inputs */
        DDX,
        DDY,
        STATE_SIZE
    };

    enum Command
    {
        /* Position Command */
        UX = 0,
        UY,
        COMMAND_SIZE
    };

    typedef Eigen::Matrix<float, STATE_SIZE, STATE_SIZE> StateTransitionMatrix;
    typedef Eigen::Matrix<float, STATE_SIZE, COMMAND_SIZE> CommandTransitionMatrix;
    typedef Eigen::Matrix<float, STATE_SIZE, 1> StateVector;

    struct Settings
    {
        /* State matrix */
        StateTransitionMatrix A;
        /* Commande Matrix */
        CommandTransitionMatrix B;
        /* controller set of gain*/
        float gainIdealModelPosition;
        float gainIdealModelVelocity;
        float gainIdealModelAcceleration;
        /* Maximum tilt angular rate reference */
        float maxTiltAngularRateRef;
        /* Maximum horizontal speed reference*/
        float maxHorizontalSpeed;
        /* Maximum Horizontal acceleration reference*/
        float maxHorizontalAcceleration;
        /* time of the propagation */
        float dt;
    };

    HorizontalIdealModel(const char* ConfigPath);
    HorizontalIdealModel(const Settings& cfg);
    ~HorizontalIdealModel() = default;

    /**
     * @brief: Perform one step of the dynamic model
     */
    void process(const StateVector& reference);

    /**
     * @brief: Return current state
     */
    const HorizontalIdealModel::StateVector& getState() const;

    /**
     * @brief set current state
     */
    void setState(const StateVector& state);

    /**
     * @brief: Set gains
     */
    void setGains(const float& gainIdealModelPosition, const float& gainIdealModelVelocity);

    /**
     * @brief: Set maximum tilt angular rate reference
     */
    void setMaxTiltAngularRateRef(float MaxTiltAngularRateRef);

    /**
     * @brief: Set maximum horizontal speed reference
     */
    void setMaxHorizontalSpeed(float maxHorizontalSpeed);

    /**
     * @brief: Set maximum horizontal acceleration reference
     */
    void setMaxHorizontalAcceleration(float maxHorizontalAcceleration);

    /**
     * @brief: Set the propagation timestep
     */
    void setTimestep(float dt);

private:
    /* Horizontal ideal model state vector */
    StateVector _state;
    /* Horizontal ideal model config */
    Settings _config;
    /* Threshold for the acceleration command */
    float _maxAccelerationCommand;

    int _fillConfigFromFile(const char* configPath);

    void _init();

}; // HorizontalIdealModel class
} // namespace physics
