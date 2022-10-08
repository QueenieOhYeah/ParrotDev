/**
 *  @brief Compute the speed of the wind at a given altitude
 *
 *  @details The model uses the formula: v2 = v1 * (h2/h1) ^ alpha
 *           where v2 is the wind speed at altitude h2,
 *           v1 the wind speed at altitude h1,
 *           alpha is the roughness coeficient of the ground
 *           a mean value is taken for alpha : surfaceCoef
 *  altitude : altRef The wind model is considered constant uder altRef.
 *
 *  Copyright (c) 2019 Parrot Drones SAS
 */

#pragma once

#include <Eigen/Eigen>

/** Forward declaration */
struct cmov_avg_filter;

namespace physics
{
class WindModel
{
public:
    WindModel();
    ~WindModel();

    /**
     * @brief Generate the mean wind value at altref altitude.
     *
     * @details Take instantaneous wind at current altitude, then project wind at altRef.
     *          The projected wind is filtered by the cumulative moving average filter.
     *          The result is saved in the class member meanWindAltRef.
     *
     * @param altCurrent actual altitude of the drone from ground level
     * @param windCart instantaneous wind at current altitude (cartesian)
     *
     */
    void generateAndFilterWindRef(float altCurrent, Eigen::Vector2f wind);

    /**
     * @brief Initialisation function to set the model parameter from
     *        the configuration
     *
     * @param windModelAltRef Reference altitude for the model
     * @param windModelSurfaceCoef Model surface coefficient
     * @param filterSize Filter size config
     * @return false if an error occurs
     *         true if success
     *
     */
    bool init(float windModelAltRef, float windModelSurfaceCoef, int filterSize);

    /**
     * @brief compute the wind at the desired altitude from the model
     *
     * @param altDes Altitude at which the wind will be computed
     *
     * @return 2d wind at desired altitude
     */
    Eigen::Vector2f getWindAtAltitude(float altDes) const;

    /**
     * @brief Clear internal cumulative moving average filter
     *        and reset input and output values to zero
     */
    void resetFilter();

    /**
     * @brief Set last cumulative moving average filter output
     *        (without reducing internal filter count)
     */
    void setFilterValue(Eigen::Vector2f newRef);

    /**
     * @brief Getter for meanWindAltRef member
     */
    Eigen::Vector2f getMeanWindAltRef() const;

    /**
     * @brief Setter for meanWindAltRef member
     * @details Can be used when you need to manually set the model values
     *          without having to feed the filter via generateAndFilterWindRef.
     *          For instance if you need to duplicate the WindModel instance
     *          in a second process, you can simply share the meanWindAltRef
     *          value each time the first filter generates it.
     */
    void setMeanWindAltRef(const Eigen::Vector2f& newRef);

private:
    /* non-copyable */
    WindModel(const WindModel&);
    WindModel& operator=(const WindModel&);

    /* Model parameters*/
    float altRef;
    float surfaceCoef;

    /* Model members*/
    struct cmov_avg_filter* filterX;
    struct cmov_avg_filter* filterY;
    Eigen::Vector2f meanWindAltRef;

    /**
     * @brief Project cartesian wind from actual drone altitude toward altRef
     *
     * @param altCurrent actual altitude of the drone from ground level
     * @param windCart wind in cartesian coordinates at altCurrent
     *
     * @return wind model at altRef in cartesian coordinates
     */
    Eigen::Vector2f generateWindRef(float altCurrent, Eigen::Vector2f windCart) const;

    /**
     * @brief Project cartesian wind from altRef altitude toward altDes altitude
     *
     * @param altDes actual altitude of the drone from ground level
     * @param windCart wind in cartesian coordinates at altRef
     *
     * @return wind model at altDes in cartesian coordinates
     */
    Eigen::Vector2f computeWindModelAtAltRef(float altDes, Eigen::Vector2f windCart) const;
};

} // namespace physics
