/**
 *  Copyright (c) 2020 Parrot Drones SAS
 */

#pragma once

#include <Eigen/Eigen>
#include <memory>

namespace physics
{
/**
 * @brief 6th order dynamic model for drone yaw
 * @details Propagation model that takes into account drone and controller dynamics around yaw axis.
 *          It takes into account maximum yaw and yaw rate but does not saturate higher order state
 *          input.
 *          Model ref are the targeted heading angle, heading rate and heading acceleration.
 *          Model outputs are a feasible 6th dimension state vector
 *          Model response can be changed by tuning the gain vector.
 *          More information are available at:
 *          https://redmine-drones.parrot.biz/attachments/download/32141/idealModel.pdf
 */

class YawIdealModel
{
public:
    enum State
    {
        ANGLE = 0,
        RATE,
        ACC,
        JERK,
        ACC_CMD,
        JERK_CMD,
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
    /* having a state feedback controller involves that the gains vector must has the size of the
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
        /* Maximum angle reference */
        float maxAngleRef;
        /* Maximum rate reference */
        float maxRateRef;
        /* Maximum acceleration reference */
        float maxAccRef;
    };

    struct References
    {
        /* Yaw reference */
        float angle;
        /* Yaw rate reference */
        float rate;
        /* Yaw acceleration input */
        float acceleration;
    };

    // FIXME make constructor private and enforce the use of the factory
    YawIdealModel(const char* configPath);
    YawIdealModel(const Settings& cfg);
    ~YawIdealModel() = default;

    /**
     * @brief Factory - config from file
     * @details Produce a nullptr in case of invalid configuration file or allocation failure
     */
    static std::unique_ptr<YawIdealModel> create(const char* configPath);

    /**
     * @brief: Perform one step of the dynamic model
     */
    void propagate(const References& ref);

    /**
     * @brief: Return current state
     */
    const YawIdealModel::StateVector& getState() const;

    /**
     * @brief: set current state
     */
    void setState(const StateVector& state);

    /**
     * @brief: Set gains
     */
    void setGains(const GainVector& gains);

    /**
     * @brief: Set maximum reference yaw
     */
    void setMaxAngleRef(float maxAngleRef);

    /**
     * @brief: Set maximum reference yaw rate
     */
    void setMaxRateRef(float maxRateRef);

private:
    /* Ideal yaw model config */
    Settings _config;
    /* Ideal yaw model state vector */
    StateVector _state;

    /**
     * @brief Fill a Settings structure from an input file
     * @details Settings structure l
     *
     * @param configPath Input config file
     * @param config Config structure to fill
     * @return 0 in case of success
     *         -EIO in case of invalid or nonexistent config file
     *         -ENOENT in case of missing or invalid parameter
     */
    static int _fillConfigFromFile(const char* configPath, Settings& config);

}; // YawIdealModel class
} // namespace physics
