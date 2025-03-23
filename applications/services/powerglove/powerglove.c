// PowerGlove
// Read GPIO pins to Nav buttons presses
// Daisy Universe [D]
// 03 . 18 . 25

#include <furi.h>
#include <input/input.h>
#include <furi_hal_gpio.h>
#include <furi/core/log.h>

// GPIO Defines, change these to change the pins you want to use
#define GPIO_BUTTON_UP      &gpio_ext_pa7
#define GPIO_BUTTON_DOWN    &gpio_ext_pa6
#define GPIO_BUTTON_LEFT    &gpio_ext_pa4
#define GPIO_BUTTON_RIGHT   &gpio_ext_pb3
#define GPIO_BUTTON_OK      &gpio_ext_pb2
#define GPIO_BUTTON_BACK    &gpio_ext_pc3

static int32_t gpio_input_worker(void* context) {
    UNUSED(context);

    // Open the input even pubsub record when the worker spawns
    FuriPubSub* input_pubsub = furi_record_open(RECORD_INPUT_EVENTS);
    InputKey key = InputKeyMAX;
    
    // Init button state bools. Might want to change all button states to one byte?
    bool pressed            = false;
    bool last_state_up      = true ;
    bool last_state_down    = true ;
    bool last_state_left    = true ;
    bool last_state_right   = true ;
    bool last_state_ok      = true ;
    bool last_state_back    = true ;


    while (true) {

        // Read all pins
        bool state_up      = furi_hal_gpio_read(GPIO_BUTTON_UP)    ;
        bool state_down    = furi_hal_gpio_read(GPIO_BUTTON_DOWN)  ;
        bool state_left    = furi_hal_gpio_read(GPIO_BUTTON_LEFT)  ;
        bool state_right   = furi_hal_gpio_read(GPIO_BUTTON_RIGHT) ;
        bool state_ok      = furi_hal_gpio_read(GPIO_BUTTON_OK)    ;
        bool state_back    = furi_hal_gpio_read(GPIO_BUTTON_BACK)  ;

        // Do stuff with them. I might be able to convert this to a case statement, need to learn more C
        if (!state_up && last_state_up) {
            FURI_LOG_E("PowerGlove", "UP");
            key     = InputKeyUp ;
            pressed = true ;
        } else if (!state_down && last_state_down)      {
            FURI_LOG_E("PowerGlove", "DOWN");
            key     = InputKeyDown ;
            pressed = true ;
        } else if (!state_left && last_state_left)      {
            FURI_LOG_E("PowerGlove", "LEFT");
            key     = InputKeyLeft ;
            pressed = true ;
        } else if (!state_right && last_state_right)    {
            FURI_LOG_E("PowerGlove", "RIGHT");
            key     = InputKeyRight ;
            pressed = true ;
        } else if (!state_ok && last_state_ok)          {
            FURI_LOG_E("PowerGlove", "OK");
            key     = InputKeyOk ;
            pressed = true ;
        } else if (!state_back && last_state_back)      {
            FURI_LOG_E("PowerGlove", "BACK");
            key     = InputKeyBack ;
            pressed = true ;
        } else {

        }

        // Update the button states
        last_state_up      = state_up    ;
        last_state_down    = state_down  ;
        last_state_left    = state_left  ;
        last_state_right   = state_right ;
        last_state_ok      = state_ok    ;
        last_state_back    = state_back  ;

        // This is how the sausage is made. If you're looking for how to invoke nav buttons, this is your man
        if(pressed) {
            InputEvent event = {
                .key = key,
                .sequence_source = INPUT_SEQUENCE_SOURCE_SOFTWARE,
                .sequence_counter = 0,
            };

            event.type = InputTypePress;
            furi_pubsub_publish(input_pubsub, &event);
            event.type = InputTypeShort;
            furi_pubsub_publish(input_pubsub, &event);
            event.type = InputTypeRelease;
            furi_pubsub_publish(input_pubsub, &event);
        }

        furi_delay_ms(100) ;
        pressed = false ;
        
        }
        // Close the pubsub record if the worker shuts down (it won't)
        furi_record_close(RECORD_INPUT_EVENTS);
        return 0;

    }  

int32_t powerglove_srv(void* p) {
    UNUSED(p) ;

    // Init all pins for PullUp reading
    furi_hal_gpio_init(GPIO_BUTTON_UP,      GpioModeInterruptFall, GpioPullUp, GpioSpeedLow) ;
    furi_hal_gpio_init(GPIO_BUTTON_DOWN,    GpioModeInterruptFall, GpioPullUp, GpioSpeedLow) ;
    furi_hal_gpio_init(GPIO_BUTTON_LEFT,    GpioModeInterruptFall, GpioPullUp, GpioSpeedLow) ;
    furi_hal_gpio_init(GPIO_BUTTON_RIGHT,   GpioModeInterruptFall, GpioPullUp, GpioSpeedLow) ;
    furi_hal_gpio_init(GPIO_BUTTON_OK,      GpioModeInterruptFall, GpioPullUp, GpioSpeedLow) ;
    furi_hal_gpio_init(GPIO_BUTTON_BACK,    GpioModeInterruptFall, GpioPullUp, GpioSpeedLow) ;

    // Create the background worker thread
    FuriThread* gpio_thread = furi_thread_alloc();
    furi_thread_set_name(gpio_thread, "GPIO_worker");
    furi_thread_set_stack_size(gpio_thread, 4096);
    furi_thread_set_callback(gpio_thread, gpio_input_worker);
    furi_thread_start(gpio_thread);

    // Keep the service alive
    while (1) {
        furi_delay_ms(1000);
    }

    // Cleanup (though it will never reach here)
    furi_thread_free(gpio_thread);
    
    return 0;
}