#pragma once

#ifdef DEBUG
#include <ostream>
/**
 * A singleton class that provides debugging utilities.
 */
class Debug {
    std::ostream& out;

    /**
     * Create a new Debug instance that writes to the given output stream.
     * @param out the output stream to write to
     */
    explicit Debug(std::ostream& out);

    ~Debug();

public:
    /**
     * Get the singleton instance that writes to std::cout.
     * @return the singleton instance that writes to std::cout
     */
    static Debug& cout();

    /**
     * Get the singleton instance that writes to std::cerr.
     * @return the singleton instance that writes to std::cerr
     */
    static Debug& cerr();

    /**
     * Print the given value to the output stream.
     * @tparam T the type of the value to print
     * @param value the value to print
     */
    template <typename T>
    void print(const T& value);

    /**
     * Flush the output stream.
     */
    void flush() const;
};

template <typename T>
void Debug::print(const T& value) {
    out << value;
}
#else

/**
 * A singleton class that provides debugging utilities.
 */
class Debug {
    /**
     * Create a new Debug instance
     */
    Debug();

    ~Debug();

public:
    /**
     * Get the singleton instance that writes to std::cout.
     * @return the singleton instance that writes to std::cout
     */
    static Debug& cout();

    /**
     * Get the singleton instance that writes to std::cerr.
     * @return the singleton instance that writes to std::cerr
     */
    static Debug& cerr();

    /**
     * Print the given value to the output stream.
     * @tparam T the type of the value to print
     * @param value the value to print
     */
    template <typename T>
    void print(const T& value);

    /**
     * Flush the output stream.
     */
    void flush() const;
};

template <typename T>
void Debug::print([[maybe_unused]] const T& value) {}

#endif
