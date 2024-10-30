#pragma once

#include "Shape2D.h"

class Capsule final: public Shape2D {
    float _radius, _heigth;

public:
    Capsule() = delete;
    Capsule(const Capsule& other);
    Capsule& operator=(const Capsule& other);
    Capsule(Capsule&& other) noexcept;
    Capsule& operator=(Capsule&& other) noexcept;
    ~Capsule() override = default;

    /**
     * Construct a new Capsule object
     * @param center the center of the capsule
     * @param rotation the rotation of the capsule
     * @param radius the radius of the capsule
     * @param height the height of the capsule
     */
    Capsule(Vector2 center, float rotation, float radius, float height);

    /**
     * Get the radius of the capsule
     * @return the radius of the capsule
     */
    [[nodiscard]] float radius() const;

    /**
     * Get the height of the capsule
     * @return the height of the capsule
     */
    [[nodiscard]] float height() const;

    /**
     * Check if this capsule intersects with a circle
     * @param circle a circle
     * @return True if the shapes intersect, false otherwise
     */
    [[nodiscard]] bool intersects(const Circle& circle) const override;

    /**
     * Check if this capsule intersects with a rectangle
     * @param rectangle a rectangle
     * @return True if the shapes intersect, false otherwise
     */
    [[nodiscard]] bool intersects(const Rectangle& rectangle) const override;

    /**
     * Check if this capsule intersects with a capsule
     * @param capsule a capsule
     * @return True if the capsules intersect, false otherwise
     */
    [[nodiscard]] bool intersects(const Capsule& capsule) const override;
};
