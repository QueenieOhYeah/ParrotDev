/**
 *  Copyright (c) 2020 Parrot Drones SAS
 */

#pragma once

#include <Eigen/Eigen>

namespace physics
{
/**
 * @brief 4th order dynamic model for the vertical motion.
 * @details Propagation model taking into account the drone vertical dynamics
 *          and the vertical controller.
 *          Model inputs reference are the targeted horizontal position, velocity and acceleration.
 *          Model outputs is an ideally modeled drone 4th dimension state vector
 *          Model response can be changed by tuning the gain vector
 */

class VerticalIdealModel
{
public:
    enum State
    {
        POS = 0,
        VEL,
        ACC,
        JERK,
        STATE_SIZE
    };

    enum Command
    {
        SNAP = 0,
        COMMAND_SIZE
    };

    typedef Eigen::Matrix<float, STATE_SIZE, STATE_SIZE> StateTransitionMatrix;
    typedef Eigen::Matrix<float, STATE_SIZE, COMMAND_SIZE> CommandTransitionMatrix;
    typedef Eigen::Matrix<float, STATE_SIZE, 1> StateVector;
    /* having a state feedback controller involves that the gains vector must have the size of the
       state vector */
    typedef Eigen::Matrix<float, STATE_SIZE, 1> GainVector;

    struct Settings
    {
        /* State transition matrix */
        StateTransitionMatrix A;
        /* Command transition matrix */
        CommandTransitionMatrix B;
        /* Controller set of gains */
        GainVector gains;
        /* Minimum vertical speed reference*/
        float minVerticalSpeed;
        /* Maximum vertical speed reference*/
        float maxVerticalSpeed;
        /* Minimum vertical acceleration reference */
        float minVerticalAcceleration;
        /* Maximum vertical acceleration reference */
        float maxVerticalAcceleration;
        /* Maximum command for height*/
        float maxHeightIdealCommand;
        /* Time of the propagation */
        float dt;
    };

    VerticalIdealModel(const char* configPath);
    VerticalIdealModel(const Settings& cfg);
    ~VerticalIdealModel() = default;

    /**
     * @brief: Perform one step of the dynamic model
     */
    void process(const StateVector& reference);

    /**
     * @brief: Return current state
     */
    const VerticalIdealModel::StateVector& getState() const;

    /**
     * @brief: set current state
     */
    void setState(const StateVector& state);

    /**
     * @brief: Set gains
     */
    void setGains(const GainVector& gains);

    /**
     * @brief: Set minimum vertical speed
     */
    void setMinVerticalSpeed(float minVerticalSpeed);

    /**
     * @brief: Set maximum vertical speed
     */
    void setMaxVerticalSpeed(float maxVerticalSpeed);

    /**
     * @brief: Set maximum vertical acceleration
     */
    void setMinVerticalAcceleration(float minVerticalAcceleration);

    /**
     * @brief: Set maximum vertical acceleration
     */
    void setMaxVerticalAcceleration(float maxVerticalAcceleration);

    /**
     * @brief: Set maximum command for height
     */
    void setMaxHeightIdealCommand(float maxHeightIdealCommand);

    /**
     * @brief set the propagation timestep
     */
    void setTimeStep(float dt);

private:
    /* Ideal vertical model config */
    Settings _config;
    /* Ideal vertical model state vector */
    StateVector _state;

    float _upVelocityCommandAccLimited;

    int _fillConfigFromFile(const char* configPath);

}; // VerticalIdealModel class
} // namespace physics
