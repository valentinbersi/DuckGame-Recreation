#pragma once

#include <list>

#include "Camera.h"
#include "DuckData.h"
#include "Force.h"
#include "Rectangle.h"
#include "Vector2.h"

class Camera {
public:
    // Constructor
    Camera(int& windowWidth, int& windowHeight);

    /**
    * Calculates the aspect ratio of the window, determines the center of all ducks,
    * and calculates the maximum distance between any two ducks. It then updates the zoom level
    * and view rectangle of the camera based on these values
    * @param ducks the list of ducks
    * @param deltaTime the time since the last update
    */
    void update(const std::list<DuckData>& ducks, float deltaTime);

    /**
     * Forces the camera to update its position and size to the center of ducks and the max distance of them
     * @param ducks the list of ducks
     */
    void forceUpdate(const std::list<DuckData>& ducks);

    /**
     * Returns the view rectangle of the camera
     * @return the view rectangle of the camera
     */
    Rectangle& getViewRect();

    // Sets "ducksArrived" to false
    void noDucksArrived();

private:
    /**
    * This method adjusts the size of the view rectangle based on the maximum distance between
    * ducks and the aspect ratio of the window. It then centers the view rectangle on the provided
    * center point
    * @param center the center point of the ducks
    * @param maxDistance the maximum distance between any two ducks
    * @param aspectRatio the aspect ratio of the window
    * @param deltaTime the time since the last update
    * @param force whether to force the camera to update
    */
    void updateZoom(const Vector2& center, const Vector2& maxDistance, float aspectRatio,
                    float deltaTime, Force = Force::No);

    struct UpdateInfo {
        Vector2 center;
        Vector2 maxDistance;
        float aspectRatio;
    };

    /**
     * Gets the info from the camera, like the aspect ratio, center, and max distance between ducks
     * @param ducks the list of ducks
     */
    UpdateInfo updateInfo(const std::list<DuckData>& ducks) const;

    /**
     * Calculates the maximum distance between any ducks in the list
     * @param ducks the list of ducks
     * @param aspectRatio the aspect ratio of the window
     */
    static Vector2 calculateMaxDistance(const std::list<DuckData>& ducks, float aspectRatio);

    /**
     * Calculates the center point of all ducks in the list
     * @param ducks the list of ducks
     */
    static Vector2 centerOfDucks(const std::list<DuckData>& ducks);

    int& windowWidth;
    int& windowHeight;
    Rectangle viewRect;
    bool ducksArrived;
};
