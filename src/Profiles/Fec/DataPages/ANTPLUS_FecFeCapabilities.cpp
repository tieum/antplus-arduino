#include <Profiles/Fec/DataPages/ANTPLUS_FecFeCapabilities.h>
#include <Profiles/Fec/ANTPLUS_FecPrivateDefines.h>

#define MAXIMUM_RESISTANCE_LSB_BYTE 5
#define MAXIMUM_RESISTANCE_MSB_BYTE 6
#define CAPABILITIES_BIT_FIELD_BYTE 7
#define MAXIMUM_RESISTANCE_INVALID 0xFFFF
#define RESERVED_LSB 1
#define RESERVED_MSB 4
#define RESERVED_VALUE 0xFFFFFFFF

template<class T>
FecBaseFeCapabilities<T>::FecBaseFeCapabilities() :
    CoreDataPage<T>() {}

template<class T>
uint16_t FecBaseFeCapabilities<T>::getMaximumResistance() {
    return this->get16BitValue(MAXIMUM_RESISTANCE_LSB_BYTE, MAXIMUM_RESISTANCE_MSB_BYTE);
}

template<class T>
uint8_t FecBaseFeCapabilities<T>::getCapabilitiesBitField() {
    return this->get8BitValue(CAPABILITIES_BIT_FIELD_BYTE);
}

template class FecBaseFeCapabilities<BroadcastData>;
template class FecBaseFeCapabilities<BroadcastDataMsg>;

FecFeCapabilities::FecFeCapabilities(AntRxDataResponse& dp) :
    FecBaseMainDataPage(dp),
    FecBaseFeCapabilities<BroadcastData>() {}

FecFeCapabilitiesMsg::FecFeCapabilitiesMsg() :
    FecBaseMainDataPageMsg(FE_CAPABILITIES_NUMBER),
    FecBaseFeCapabilities<BroadcastDataMsg>() {
    this->set32BitValue(RESERVED_VALUE, RESERVED_LSB, RESERVED_MSB);
    setMaximumResistance(MAXIMUM_RESISTANCE_INVALID);
}

void FecFeCapabilitiesMsg::setMaximumResistance(uint16_t maximumResistance) {
    set16BitValue(maximumResistance, MAXIMUM_RESISTANCE_LSB_BYTE, MAXIMUM_RESISTANCE_MSB_BYTE);
}

void FecFeCapabilitiesMsg::setCapabitiliesBitField(uint8_t capabilities) {
    set8BitValue(capabilities, CAPABILITIES_BIT_FIELD_BYTE);
}

