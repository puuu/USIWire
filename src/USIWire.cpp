/*
  USIWire.cpp - USI based TWI/I2C library for Arduino
  Copyright (c) 2017 Puuu.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

  Based on TwoWire form Arduino https://github.com/arduino/Arduino.
*/

extern "C" {
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include "utility/twi.h"
}

#include "USIWire.h"

// Initialize Class Variables //////////////////////////////////////////////////

uint8_t USIWire::rxBuffer[BUFFER_LENGTH];
uint8_t USIWire::rxBufferIndex = 0;
uint8_t USIWire::rxBufferLength = 0;

uint8_t USIWire::txBuffer[BUFFER_LENGTH];
uint8_t USIWire::txBufferIndex = 0;
uint8_t USIWire::txBufferLength = 0;

uint8_t USIWire::transmitting = 0;

// Constructors ////////////////////////////////////////////////////////////////

USIWire::USIWire() {
}

// Public Methods //////////////////////////////////////////////////////////////

void USIWire::begin(void) {
  rxBufferIndex = 0;
  rxBufferLength = 0;

  txBufferIndex = 0;
  txBufferLength = 0;

  twi_init();
}

void USIWire::begin(uint8_t address) {
  twi_setAddress(address);
  twi_attachSlaveTxEvent(onRequestService);
  twi_attachSlaveRxEvent(onReceiveService);
  begin();
}

void USIWire::begin(int address) {
  begin((uint8_t)address);
}

void USIWire::end(void) {
  twi_disable();
}

void USIWire::setClock(uint32_t clock) {
  twi_setFrequency(clock);
}

uint8_t USIWire::requestFrom(uint8_t address, uint8_t quantity,
                             uint32_t iaddress, uint8_t isize,
                             uint8_t sendStop) {
  if (isize > 0) {
    // send internal address; this mode allows sending a repeated
    // start to access some devices' internal registers. This function
    // is executed by the hardware TWI module on other processors (for
    // example Due's TWI_IADR and TWI_MMR registers)

    beginTransmission(address);

    // the maximum size of internal address is 3 bytes
    if (isize > 3) {
      isize = 3;
    }

    // write internal register address - most significant byte first
    while (isize-- > 0) {
      write((uint8_t)(iaddress >> (isize*8)));
    }
    endTransmission(false);
  }

  // clamp to buffer length
  if (quantity > BUFFER_LENGTH) {
    quantity = BUFFER_LENGTH;
  }
  // perform blocking read into buffer
  uint8_t read = twi_readFrom(address, rxBuffer, quantity, sendStop);
  // set rx buffer iterator vars
  rxBufferIndex = 0;
  rxBufferLength = read;

  return read;
}

uint8_t USIWire::requestFrom(uint8_t address, uint8_t quantity,
                             uint8_t sendStop) {
  return requestFrom((uint8_t)address, (uint8_t)quantity, (uint32_t)0,
                     (uint8_t)0, (uint8_t)sendStop);
}

uint8_t USIWire::requestFrom(uint8_t address, uint8_t quantity) {
  return requestFrom((uint8_t)address, (uint8_t)quantity, (uint8_t)true);
}

uint8_t USIWire::requestFrom(int address, int quantity) {
  return requestFrom((uint8_t)address, (uint8_t)quantity, (uint8_t)true);
}

uint8_t USIWire::requestFrom(int address, int quantity, int sendStop) {
  return requestFrom((uint8_t)address, (uint8_t)quantity, (uint8_t)sendStop);
}

void USIWire::beginTransmission(uint8_t address) {
  // indicate that we are transmitting
  transmitting = 1;
  // set address of targeted slave
  txAddress = address;
  // reset tx buffer iterator vars
  txBufferIndex = 0;
  txBufferLength = 0;
}

void USIWire::beginTransmission(int address) {
  beginTransmission((uint8_t)address);
}

uint8_t USIWire::endTransmission(uint8_t sendStop) {
  // transmit buffer (blocking)
  uint8_t ret = twi_writeTo(txAddress, txBuffer, txBufferLength, 1, sendStop);
  // reset tx buffer iterator vars
  txBufferIndex = 0;
  txBufferLength = 0;
  // indicate that we are done transmitting
  transmitting = 0;
  return ret;
}

uint8_t USIWire::endTransmission(void) {
  return endTransmission(true);
}

// must be called in:
// slave tx event callback
// or after beginTransmission(address)
size_t USIWire::write(uint8_t data) {
  if (transmitting) { // in master transmitter mode
    // don't bother if buffer is full
    if (txBufferLength >= BUFFER_LENGTH) {
      setWriteError();
      return 0;
    }
    // put byte in tx buffer
    txBuffer[txBufferIndex] = data;
    ++txBufferIndex;
    // update amount in buffer
    txBufferLength = txBufferIndex;
  } else { // in slave send mode
    // reply to master
    twi_transmit(&data, 1);
  }
  return 1;
}

// must be called in:
// slave tx event callback
// or after beginTransmission(address)
size_t USIWire::write(const uint8_t *data, size_t quantity) {
  if (transmitting) { // in master transmitter mode
    for (size_t i = 0; i < quantity; ++i) {
      write(data[i]);
    }
  } else { // in slave send mode
    // reply to master
    twi_transmit(data, quantity);
  }
  return quantity;
}

// must be called in:
// slave rx event callback
// or after requestFrom(address, numBytes)
int USIWire::available(void) {
  return rxBufferLength - rxBufferIndex;
}

// must be called in:
// slave rx event callback
// or after requestFrom(address, numBytes)
int USIWire::read(void) {
  int value = -1;

  // get each successive byte on each call
  if (rxBufferIndex < rxBufferLength) {
    value = rxBuffer[rxBufferIndex];
    ++rxBufferIndex;
  }

  return value;
}

// must be called in:
// slave rx event callback
// or after requestFrom(address, numBytes)
int USIWire::peek(void) {
  int value = -1;

  if (rxBufferIndex < rxBufferLength) {
    value = rxBuffer[rxBufferIndex];
  }

  return value;
}

void USIWire::flush(void) {
  // XXX: to be implemented.
}

// sets function called on slave write
void USIWire::onReceive( void (*function)(int) ) {
  user_onReceive = function;
}

// sets function called on slave read
void USIWire::onRequest( void (*function)(void) ) {
  user_onRequest = function;
}

// Preinstantiate Objects //////////////////////////////////////////////////////

USIWire Wire = USIWire();
