/*
MD_IS31FL3741 - Library for using a MAX7219/7221 LED matrix controller

See header file for comments

This file contains class and hardware related methods.

Copyright (C) 2012-14 Marco Colli. All rights reserved.

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
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
 */
#include <Arduino.h>
#include <Wire.h>
#include "MD_IS31FL3741.h"
#include "MD_IS31FL3741_lib.h"


byte addrmap[351][2] = {(0x0, 0),  (0x1, 0),  (0x2, 0),  (0x3, 0),  (0x4, 0),  (0x5, 0),  (0x6, 0),  (0x7, 0),  (0x8, 0),  (0x9, 0),  (0xa, 0),  (0xb, 0),  (0xc, 0),  (0xd, 0),  (0xe, 0),  (0xf, 0),  (0x10, 0),  (0x11, 0),  (0x12, 0),  (0x13, 0),  (0x14, 0),  (0x15, 0),  (0x16, 0),  (0x17, 0),  (0x18, 0),  (0x19, 0),  (0x1a, 0),  (0x1b, 0),  (0x1c, 0),  (0x1d, 0),  (0x5a, 1),  (0x5b, 1),  (0x5c, 1),  (0x5d, 1),  (0x5e, 1),  (0x5f, 1),  (0x60, 1),  (0x61, 1),  (0x62, 1),  
(0x1e, 0),  (0x1f, 0),  (0x20, 0),  (0x21, 0),  (0x22, 0),  (0x23, 0),  (0x24, 0),  (0x25, 0),  (0x26, 0),  (0x27, 0),  (0x28, 0),  (0x29, 0),  (0x2a, 0),  (0x2b, 0),  (0x2c, 0),  (0x2d, 0),  (0x2e, 0),  (0x2f, 0),  (0x30, 0),  (0x31, 0),  (0x32, 0),  (0x33, 0),  (0x34, 0),  (0x35, 0),  (0x36, 0),  (0x37, 0),  (0x38, 0),  (0x39, 0),  (0x3a, 0),  (0x3b, 0),  (0x63, 1),  (0x64, 1),  (0x65, 1),  (0x66, 1),  (0x67, 1),  (0x68, 1),  (0x69, 1),  (0x6a, 1),  (0x6b, 1),  
(0x3c, 0),  (0x3d, 0),  (0x3e, 0),  (0x3f, 0),  (0x40, 0),  (0x41, 0),  (0x42, 0),  (0x43, 0),  (0x44, 0),  (0x45, 0),  (0x46, 0),  (0x47, 0),  (0x48, 0),  (0x49, 0),  (0x4a, 0),  (0x4b, 0),  (0x4c, 0),  (0x4d, 0),  (0x4e, 0),  (0x4f, 0),  (0x50, 0),  (0x51, 0),  (0x52, 0),  (0x53, 0),  (0x54, 0),  (0x55, 0),  (0x56, 0),  (0x57, 0),  (0x58, 0),  (0x59, 0),  (0x6c, 1),  (0x6d, 1),  (0x6e, 1),  (0x6f, 1),  (0x70, 1),  (0x71, 1),  (0x72, 1),  (0x73, 1),  (0x74, 1),  
(0x5a, 0),  (0x5b, 0),  (0x5c, 0),  (0x5d, 0),  (0x5e, 0),  (0x5f, 0),  (0x60, 0),  (0x61, 0),  (0x62, 0),  (0x63, 0),  (0x64, 0),  (0x65, 0),  (0x66, 0),  (0x67, 0),  (0x68, 0),  (0x69, 0),  (0x6a, 0),  (0x6b, 0),  (0x6c, 0),  (0x6d, 0),  (0x6e, 0),  (0x6f, 0),  (0x70, 0),  (0x71, 0),  (0x72, 0),  (0x73, 0),  (0x74, 0),  (0x75, 0),  (0x76, 0),  (0x77, 0),  (0x75, 1),  (0x76, 1),  (0x77, 1),  (0x78, 1),  (0x79, 1),  (0x7a, 1),  (0x7b, 1),  (0x7c, 1),  (0x7d, 1),  
(0x78, 0),  (0x79, 0),  (0x7a, 0),  (0x7b, 0),  (0x7c, 0),  (0x7d, 0),  (0x7e, 0),  (0x7f, 0),  (0x80, 0),  (0x81, 0),  (0x82, 0),  (0x83, 0),  (0x84, 0),  (0x85, 0),  (0x86, 0),  (0x87, 0),  (0x88, 0),  (0x89, 0),  (0x8a, 0),  (0x8b, 0),  (0x8c, 0),  (0x8d, 0),  (0x8e, 0),  (0x8f, 0),  (0x90, 0),  (0x91, 0),  (0x92, 0),  (0x93, 0),  (0x94, 0),  (0x95, 0),  (0x7e, 1),  (0x7f, 1),  (0x80, 1),  (0x81, 1),  (0x82, 1),  (0x83, 1),  (0x84, 1),  (0x85, 1),  (0x86, 1),  
(0x96, 0),  (0x97, 0),  (0x98, 0),  (0x99, 0),  (0x9a, 0),  (0x9b, 0),  (0x9c, 0),  (0x9d, 0),  (0x9e, 0),  (0x9f, 0),  (0xa0, 0),  (0xa1, 0),  (0xa2, 0),  (0xa3, 0),  (0xa4, 0),  (0xa5, 0),  (0xa6, 0),  (0xa7, 0),  (0xa8, 0),  (0xa9, 0),  (0xaa, 0),  (0xab, 0),  (0xac, 0),  (0xad, 0),  (0xae, 0),  (0xaf, 0),  (0xb0, 0),  (0xb1, 0),  (0xb2, 0),  (0xb3, 0),  (0x87, 1),  (0x88, 1),  (0x89, 1),  (0x8a, 1),  (0x8b, 1),  (0x8c, 1),  (0x8d, 1),  (0x8e, 1),  (0x8f, 1),  
(0x0, 1),  (0x1, 1),  (0x2, 1),  (0x3, 1),  (0x4, 1),  (0x5, 1),  (0x6, 1),  (0x7, 1),  (0x8, 1),  (0x9, 1),  (0xa, 1),  (0xb, 1),  (0xc, 1),  (0xd, 1),  (0xe, 1),  (0xf, 1),  (0x10, 1),  (0x11, 1),  (0x12, 1),  (0x13, 1),  (0x14, 1),  (0x15, 1),  (0x16, 1),  (0x17, 1),  (0x18, 1),  (0x19, 1),  (0x1a, 1),  (0x1b, 1),  (0x1c, 1),  (0x1d, 1),  (0x90, 1),  (0x91, 1),  (0x92, 1),  (0x93, 1),  (0x94, 1),  (0x95, 1),  (0x96, 1),  (0x97, 1),  (0x98, 1),  
(0x1e, 1),  (0x1f, 1),  (0x20, 1),  (0x21, 1),  (0x22, 1),  (0x23, 1),  (0x24, 1),  (0x25, 1),  (0x26, 1),  (0x27, 1),  (0x28, 1),  (0x29, 1),  (0x2a, 1),  (0x2b, 1),  (0x2c, 1),  (0x2d, 1),  (0x2e, 1),  (0x2f, 1),  (0x30, 1),  (0x31, 1),  (0x32, 1),  (0x33, 1),  (0x34, 1),  (0x35, 1),  (0x36, 1),  (0x37, 1),  (0x38, 1),  (0x39, 1),  (0x3a, 1),  (0x3b, 1),  (0x99, 1),  (0x9a, 1),  (0x9b, 1),  (0x9c, 1),  (0x9d, 1),  (0x9e, 1),  (0x9f, 1),  (0xa0, 1),  (0xa1, 1),  
(0x3c, 1),  (0x3d, 1),  (0x3e, 1),  (0x3f, 1),  (0x40, 1),  (0x41, 1),  (0x42, 1),  (0x43, 1),  (0x44, 1),  (0x45, 1),  (0x46, 1),  (0x47, 1),  (0x48, 1),  (0x49, 1),  (0x4a, 1),  (0x4b, 1),  (0x4c, 1),  (0x4d, 1),  (0x4e, 1),  (0x4f, 1),  (0x50, 1),  (0x51, 1),  (0x52, 1),  (0x53, 1),  (0x54, 1),  (0x55, 1),  (0x56, 1),  (0x57, 1),  (0x58, 1),  (0x59, 1),  (0xa2, 1),  (0xa3, 1),  (0xa4, 1),  (0xa5, 1),  (0xa6, 1),  (0xa7, 1),  (0xa8, 1),  (0xa9, 1),  (0xaa, 1)
};




/**
 * \file
 * \brief Implements class definition and general methods
 */

MD_IS31FL3741::MD_IS31FL3741(uint8_t i2caddr): //updated
_i2caddr(i2caddr), _updateEnabled(true)
{
  setModuleParameters(mod);
}

MD_IS31FL3741::MD_IS31FL3741(moduleType_t i2caddr): //updated
_i2caddr(0), _updateEnabled(true)
{
  setModuleParameters(mod);
}



void MD_IS31FL3741::begin(void) //updated
{


  // object memory and internals
  setShiftDataInCallback(nullptr);
  setShiftDataOutCallback(nullptr);

  _matrix = (deviceInfo_t *)malloc(sizeof(deviceInfo_t));
  _i2cData = (uint8_t *)malloc(I2C_DATA_SIZE);

#if USE_LOCAL_FONT
  setFont(_sysfont);
#endif // INCLUDE_LOCAL_FONT

  //Init I2C

  /*control(TEST, OFF);                   // no test
  control(SCANLIMIT, ROW_SIZE-1);       // scan limit is set to max on startup
  control(INTENSITY, MAX_INTENSITY/2);  // set intensity to a reasonable value
  control(DECODE, OFF);                 // ensure no decoding (warm boot potential issue)
  clear();
  control(SHUTDOWN, OFF);               // take the modules out of shutdown mode
*/


}

MD_IS31FL3741::~MD_IS31FL3741(void) //updated
{
  free(_matrix);
  free(_i2cData);
}

void MD_IS31FL3741::controlHardware(controlRequest_t mode, int value)
// control command is for the devices, translate internal request to device bytes
// into the transmission buffer
{
  uint8_t opcode = OP_NOOP;
  uint8_t param = 0;

  // work out data to write
  switch (mode)
  {
    case SHUTDOWN:
      opcode = OP_SHUTDOWN;
      param = (value == OFF ? 1 : 0);
      break;

    case SCANLIMIT:
      opcode = OP_SCANLIMIT;
      param = (value > MAX_SCANLIMIT ? MAX_SCANLIMIT : value);
      break;

    case INTENSITY:
      opcode = OP_INTENSITY;
      param = (value > MAX_INTENSITY ? MAX_INTENSITY : value);
      break;

    case DECODE:
      opcode = OP_DECODEMODE;
      param = (value == OFF ? 0 : 0xff);
      break;

    case TEST:
      opcode = OP_DISPLAYTEST;
      param = (value == OFF ? 0 : 1);
      break;

    default:
      return;
  }

  // put our device data into the buffer TODO
  //_spiData[SPI_OFFSET(dev, 0)] = opcode;
  //_spiData[SPI_OFFSET(dev, 1)] = param;
}

void MD_IS31FL3741::controlLibrary(controlRequest_t mode, int value)
// control command was internal, set required parameters
{
  switch (mode)
  {
    case UPDATE:
      _updateEnabled = (value == ON);
    if (_updateEnabled) flushBufferAll();
      break;

    case WRAPAROUND:
      _wrapAround = (value == ON);
      break;

    default:
      break;
  }
}

bool MD_IS31FL3741::control(uint8_t startDev, uint8_t endDev, controlRequest_t mode, int value)
{
  if (endDev < startDev) return(false);

  if (mode < UPDATE)  // device based con
  {
    i2cClearBuffer();
    controlHardware(mode, value);
    i2cSend();
  }
  else                // internal control function, doesn't relate to specific device
  {
    controlLibrary(mode, value);
  }

  return(true);
}

bool MD_IS31FL3741::control(uint8_t buf, controlRequest_t mode, int value)
// dev is zero based and needs adjustment if used
{
  if (buf > LAST_BUFFER) return(false);

  if (mode < UPDATE)  // device based control
  {
    i2cClearBuffer();
    controlHardware(buf, mode, value);
    i2cSend();
  }
  else                // internal control function, doesn't relate to specific device
  {
    controlLibrary(mode, value);
  }

  return(true);
}

void MD_IS31FL3741::flushBufferAll()
// Only one data byte is sent to a device, so if there are many changes, it is more
// efficient to send a data byte all devices at the same time, substantially cutting
// the number of communication messages required.
{
  for (uint8_t i=0; i<ROW_SIZE; i++)  // all data rows
  {
    bool bChange = false; // set to true if we detected a change

    i2cClearBuffer();

    for (uint8_t dev = FIRST_BUFFER; dev <= LAST_BUFFER; dev++)	// all devices
    {
      if (bitRead(_matrix[dev].changed, i))
      {
        // put our device data into the buffer  ==TODO==
        //_spiData[SPI_OFFSET(dev, 0)] = OP_DIGIT0+i;
        //_spiData[SPI_OFFSET(dev, 1)] = _matrix[dev].dig[i];
        bChange = true;
      }
    }

  if (bChange) i2cSend();
  }

  // mark everything as cleared
  for (uint8_t dev = FIRST_BUFFER; dev <= LAST_BUFFER; dev++)
    _matrix[dev].changed = ALL_CLEAR;
}

void MD_IS31FL3741::flushBuffer(uint8_t buf)
// Use this function when the changes are limited to one device only.
// Address passed is a buffer address
{
  PRINT("\nflushBuf: ", buf);
  PRINTS(" r");

  if (buf > LAST_BUFFER)
    return;

  for (uint8_t i = 0; i < ROW_SIZE; i++)
  {
    if (bitRead(_matrix[buf].changed, i))
    {
      PRINT("", i);
      i2cClearBuffer();

      // put our device data into the buffer  TODO
      //_spiData[SPI_OFFSET(buf, 0)] = OP_DIGIT0+i;
      //_spiData[SPI_OFFSET(buf, 1)] = _matrix[buf].dig[i];

      i2cSend();
    }
  }
  _matrix[buf].changed = ALL_CLEAR;
}

void MD_IS31FL3741::spiClearBuffer(void)
// Clear out the spi data array
{
  memset(_i2cData, OP_NOOP, I2C_DATA_SIZE);
}

void MD_IS31FL3741::i2cSend() 
{
  // initialize the I2C transaction
  Wire.write(_i2caddr);
  

  // shift out the data
  for (uint16_t i = 0; i < I2C_DATA_SIZE; i++)
    Wire.write(_spiData[i]);
  

  // end the I2C transaction
  Wire.endTransmission();
}

/*
Wire.beginTransmission(Dev_Add); // transmit to device IS31FL373x
 Wire.write((byte)Reg_Add); // sends regaddress
 Wire.write((byte)Reg_Dat); // sends regaddress
 Wire.endTransmission(); // stop transmitting
 */