// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <stdlib.h>
#ifdef _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif
#include <stddef.h>
#include "gballoc.h"
#include "pio.h"

typedef struct PIO_INSTANCE_TAG
{
    const PIO_INTERFACE_DESCRIPTION* pio_interface_description;
    PIO_HANDLE concrete_pio_handle;
} PIO_INSTANCE;

PIO_HANDLE pio_create(
    const PIO_INTERFACE_DESCRIPTION* io_interface_description,
    const void* pio_create_parameters,
    LOGGER_LOG logger_log
)
{
    PIO_INSTANCE* pio_instance;
    if ((io_interface_description == NULL) ||
        (io_interface_description->concrete_pio_create == NULL) ||
        (io_interface_description->concrete_pio_destroy == NULL) ||
        (io_interface_description->concrete_pio_open == NULL) ||
        (io_interface_description->concrete_pio_close == NULL) ||
        (io_interface_description->concrete_pio_send == NULL) ||
        (io_interface_description->concrete_pio_receive == NULL))
    {
        pio_instance = NULL;
    }
    else
    {
        pio_instance = (PIO_INSTANCE*)malloc(sizeof(PIO_INSTANCE));

        if (pio_instance != NULL)
        {
            pio_instance->pio_interface_description = io_interface_description;

            pio_instance->concrete_pio_handle = pio_instance->
                pio_interface_description->concrete_pio_create(
                    (void*)pio_create_parameters,
                    logger_log
                );

            if (pio_instance->concrete_pio_handle == NULL)
            {
                free(pio_instance);
                pio_instance = NULL;
            }
        }
    }

    return (PIO_HANDLE)pio_instance;
}

void pio_destroy(PIO_HANDLE pio)
{
    if (pio != NULL)
    {
        PIO_INSTANCE* pio_instance = (PIO_INSTANCE*)pio;
        pio_instance->
            pio_interface_description->concrete_pio_destroy(
                pio_instance->concrete_pio_handle
            );
        free(pio_instance);
    }
}

int pio_open(
    PIO_HANDLE pio,
    ON_PIO_OPEN_COMPLETE on_pio_open_complete,
    void* callback_context
)
{
    int result;

    if (pio == NULL)
    {
        result = __LINE__;
    }
    else
    {
        PIO_INSTANCE* pio_instance = (PIO_INSTANCE*)pio;

        if (pio_instance->
                pio_interface_description->concrete_pio_open(
                    pio_instance->concrete_pio_handle,
                    on_pio_open_complete,
                    callback_context
                ) != 0)
        {
            result = __LINE__;
        }
        else
        {
            result = 0;
        }
    }

    return result;
}

int pio_close(PIO_HANDLE pio, ON_PIO_CLOSE_COMPLETE on_pio_close_complete, void* callback_context)
{
    int result;

    if (pio == NULL)
    {
        result = __LINE__;
    }
    else
    {
        PIO_INSTANCE* pio_instance = (PIO_INSTANCE*)pio;

        if (pio_instance->
                pio_interface_description->concrete_pio_close(
                    pio_instance->concrete_pio_handle,
                    on_pio_close_complete,
                    callback_context
                ) != 0)
        {
            result = __LINE__;
        }
        else
        {
            result = 0;
        }
    }

    return result;
}

int pio_send(
    PIO_HANDLE pio,
    const void* send_parameters,
    const void* buffer,
    size_t size,
    ON_PIO_SEND_COMPLETE on_send_complete,
    void* callback_context
)
{
    int result;

    if (pio == NULL)
    {
        result = __LINE__;
    }
    else
    {
        PIO_INSTANCE* pio_instance = (PIO_INSTANCE*)pio;
        result = pio_instance->
                    pio_interface_description->
                    concrete_pio_send(
                        pio_instance->concrete_pio_handle,
                        send_parameters,
                        buffer,
                        size,
                        on_send_complete,
                        callback_context
                    );
    }

    return result;
}

int pio_receive(
    PIO_HANDLE pio,
    const void* receive_parameters,
    size_t size,
    ON_PIO_RECEIVE_COMPLETE on_receive_complete,
    void* callback_context
)
{
    int result;

    if (pio == NULL)
    {
        result = __LINE__;
    }
    else
    {
        PIO_INSTANCE* pio_instance = (PIO_INSTANCE*)pio;
        result = pio_instance->
            pio_interface_description->
            concrete_pio_receive(
                pio_instance->concrete_pio_handle,
                receive_parameters,
                size,
                on_receive_complete,
                callback_context
            );
    }

    return result;
}
