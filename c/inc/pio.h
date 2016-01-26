// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef PIO_H
#define PIO_H

#include "xlogging.h"

#ifdef __cplusplus
#include <cstddef>
extern "C" {
#else
#include <stddef.h>
#endif /* __cplusplus */

typedef struct PIO_INSTANCE_TAG* PIO_HANDLE;
typedef void* CONCRETE_PIO_HANDLE;

typedef enum PIO_SEND_RESULT_TAG
{
    PIO_SEND_OK,
    PIO_SEND_ERROR,
    PIO_SEND_CANCELLED
} PIO_SEND_RESULT;

typedef enum PIO_OPEN_RESULT_TAG
{
    PIO_OPEN_OK,
    PIO_OPEN_ERROR,
    PIO_OPEN_CANCELLED
} PIO_OPEN_RESULT;

typedef void(*ON_PIO_SEND_COMPLETE)(void* context, PIO_SEND_RESULT send_result);
typedef void(*ON_PIO_RECEIVE_COMPLETE)(void* context, const unsigned char* buffer, size_t size);
typedef void(*ON_PIO_OPEN_COMPLETE)(void* context, PIO_OPEN_RESULT open_result);
typedef void(*ON_PIO_CLOSE_COMPLETE)(void* context);
typedef void(*ON_PIO_ERROR)(void* context);

typedef CONCRETE_PIO_HANDLE(*PIO_CREATE)(void* pio_create_parameters, LOGGER_LOG logger_log);
typedef void(*PIO_DESTROY)(CONCRETE_PIO_HANDLE concrete_pio);
typedef int(*PIO_OPEN)(CONCRETE_PIO_HANDLE concrete_pio, ON_PIO_OPEN_COMPLETE on_pio_open_complete, void* callback_context);
typedef int(*PIO_CLOSE)(CONCRETE_PIO_HANDLE concrete_pio, ON_PIO_CLOSE_COMPLETE on_pio_close_complete, void* callback_context);
typedef int(*PIO_SEND)(CONCRETE_PIO_HANDLE concrete_pio, const void* send_parameters, const void* buffer, size_t size, ON_PIO_SEND_COMPLETE on_send_complete, void* callback_context);
typedef int(*PIO_RECEIVE)(CONCRETE_PIO_HANDLE concrete_pio, const void* receive_parameters, size_t size, ON_PIO_RECEIVE_COMPLETE on_receive_complete, void* callback_context);

typedef struct PIO_INTERFACE_DESCRIPTION_TAG
{
    PIO_CREATE concrete_pio_create;
    PIO_DESTROY concrete_pio_destroy;
    PIO_OPEN concrete_pio_open;
    PIO_CLOSE concrete_pio_close;
    PIO_SEND concrete_pio_send;
    PIO_RECEIVE concrete_pio_receive;
} PIO_INTERFACE_DESCRIPTION;

extern PIO_HANDLE   pio_create  (const PIO_INTERFACE_DESCRIPTION* pio_interface_description, const void* pio_create_parameters, LOGGER_LOG logger_log);
extern       void   pio_destroy (PIO_HANDLE pio);
extern        int   pio_open    (PIO_HANDLE pio, ON_PIO_OPEN_COMPLETE on_pio_open_complete, void* callback_context);
extern        int   pio_close   (PIO_HANDLE pio, ON_PIO_CLOSE_COMPLETE on_pio_close_complete, void* callback_context);
extern        int   pio_send    (PIO_HANDLE pio, const void* send_parameters, const void* buffer, size_t size, ON_PIO_SEND_COMPLETE on_send_complete, void* callback_context);
extern        int   pio_receive (PIO_HANDLE pio, const void* receive_parameters, size_t size, ON_PIO_RECEIVE_COMPLETE on_receive_complete, void* callback_context);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* PIO_H */
