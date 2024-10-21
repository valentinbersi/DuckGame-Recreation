#pragma once


enum MessageType : unsigned char { INPUT = 0x0, NEWMATCH = 0x1, JOINMATCH = 0x2, STARTMATCH = 0x3 };
// class MessageType {
// public:
//     enum Value : unsigned char { Input = 0x0, NewMatch = 0x1, JoinMatch = 0x2, StartMatch = 0x3
//     };

//     MessageType(const MessageType& other);
//     MessageType& operator=(const MessageType& other);
//     MessageType(MessageType&& other) noexcept;
//     MessageType& operator=(MessageType&& other) noexcept;
//     ~MessageType();

//     MessageType() = delete;

//     /**
//      * Construct a BoxID with the given value
//      * @param value The value of the BoxID
//      */
//     // cppcheck-suppress noExplicitConstructor
//     MessageType(Value value);  // Implicit on purpose so it can be used as a common enum

//     /**
//      * Assign a BoxID with the given value
//      * @param value The value of the BoxID
//      * @return A reference to the BoxID
//      */
//     MessageType& operator=(Value value);

//     /**
//      * Construct a BoxID with the given value
//      * @param value The value of the BoxID
//      * @pre @code value@endcode should be a valid BoxID value
//      */
//     // cppcheck-suppress noExplicitConstructor
//     MessageType(unsigned char value);  // Implicit on purpose so it can be used as a common enum

//     /**
//      * Assign a BoxID with the given value
//      * @param value The value of the BoxID
//      * @return A reference to the BoxID
//      * @pre @code value@endcode should be a valid BoxID value
//      */
//     MessageType& operator=(unsigned char value);

//     /**
//      * So the BoxID can be used as an enum
//      */
//     [[nodiscard]] operator Value() const;

//     /**
//      * Compare two BoxID
//      * @param boxId The BoxID to compare
//      * @return @code true@endcode if the BoxID are equal, @code false@endcode otherwise
//      */
//     bool operator==(MessageType boxId) const;

//     /**
//      * Compare two BoxID
//      * @param boxId The BoxID to compare
//      * @return @code true@endcode if the BoxID are different, @code false@endcode otherwise
//      */
//     bool operator!=(MessageType boxId) const;

//     /**
//      * Checks if an unsigned char is a valid BoxID _value
//      * @param value The value to check
//      * @return @code true@endcode if @code value@endcode is a valid BoxID value, @code
//      false@endcode
//      * otherwise
//      */
//     static bool validMessageType(unsigned char value);

// private:
//     Value _value;
// };
