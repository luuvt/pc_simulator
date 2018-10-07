
/**
 * @file main
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include <stdlib.h>
#include <unistd.h>
#include <SDL2/SDL.h>
#include "lvgl/lvgl.h"
#include "lv_drivers/display/monitor.h"
#include "lv_drivers/indev/mouse.h"
#include "lv_examples/lv_apps/demo/demo.h"
#include "lv_examples/lv_apps/benchmark/benchmark.h"
#include "lv_examples/lv_apps/terminal/terminal.h"
#include "lv_examples/lv_apps/sysmon/sysmon.h"
#include "lv_examples/lv_tests/lv_test_theme/lv_test_theme.h"

#include "lv_examples/lv_tests/lv_test_group/lv_test_group.h"
#include "lv_examples/lv_tests/lv_test_objx/lv_test_img/lv_test_img.h"
#include "lv_examples/lv_tests/lv_test_objx/lv_test_win/lv_test_win.h"
#include "lv_examples/lv_tests/lv_test_objx/lv_test_slider/lv_test_slider.h"
#include "lv_examples/lv_tests/lv_test_objx/lv_test_roller/lv_test_roller.h"
#include "lv_examples/lv_tests/lv_test_objx/lv_test_mbox/lv_test_mbox.h"
#include "lv_examples/lv_tests/lv_test_objx/lv_test_led/lv_test_led.h"
#include "lv_examples/lv_tests/lv_test_objx/lv_test_kb/lv_test_kb.h"
#include "lv_examples/lv_tests/lv_test_objx/lv_test_chart/lv_test_chart.h"
#include "lv_examples/lv_tests/lv_test_objx/lv_test_gauge/lv_test_gauge.h"

#include "lv_examples/lv_tutorial/2_objects/lv_tutorial_objects.h"
#include "lv_examples/lv_tutorial/5_antialiasing/lv_tutorial_antialiasing.h"
#include "lv_examples/lv_tutorial/3_styles/lv_tutorial_styles.h"
#include "lv_examples/lv_tutorial/7_fonts/lv_tutorial_fonts.h"
#include "lv_examples/lv_tutorial/8_animations/lv_tutorial_animations.h"
#include "lv_examples/lv_tutorial/9_responsive/lv_tutorial_responsive.h"
#include "lv_examples/lv_tutorial/10_keyboard/lv_tutorial_keyboard.h"

#include "lv_examples/lv_tutorial/11_animations_image/lv_tutorial_animations_image.h"
#include "lib/lodepng.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void hal_init(void);
static int tick_thread(void *data);

static void gif_task(void * img_obj);
static void git_load_file(lv_img_dsc_t *img, const char *file_name);
/**********************
 *  STATIC VARIABLES
 **********************/
lv_img_dsc_t png_dsc_0;
lv_img_dsc_t png_dsc_1;
lv_img_dsc_t png_dsc_2;
lv_img_dsc_t png_dsc_3;
lv_img_dsc_t png_dsc_4;
lv_img_dsc_t png_dsc_5;

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/
//lv_obj_t *terminal;

int main(int argc, char** argv)
{
    /*Initialize LittlevGL*/
    lv_init();

    /*Initialize the HAL for LittlevGL*/
    hal_init();

    git_load_file(&png_dsc_0, "wifi_0.png");
    git_load_file(&png_dsc_1, "wifi_1.png");
    git_load_file(&png_dsc_2, "wifi_2.png");
    git_load_file(&png_dsc_3, "wifi_3.png");
    git_load_file(&png_dsc_4, "wifi_4.png");
    git_load_file(&png_dsc_5, "wifi_5.png");
    /*Create an image object and set the decoded PNG image as it's source*/
    lv_obj_t * gif_img = lv_img_create(lv_scr_act(), NULL);     /*Create the an image object in LittlevGL*/
    lv_img_set_src(gif_img, &png_dsc_0);                          /*Set the image source to the decoded PNG*/
    lv_obj_set_drag(gif_img, true);                             /*Make to image dragable*/
//    lv_obj_set_pos(gif_img, 100, 100);       /*Set a position. It will be the animation's destination*/
    
    lv_style_scr.body.main_color = LV_COLOR_MAKE(0x40, 0x70, 0xAA);
    
    lv_task_create(gif_task, 500, LV_TASK_PRIO_MID, gif_img); 

    /*Load a demo*/
    // demo_create();

    /*Try the benchmark to see how fast is your GUI*/
    // benchmark_create();

    /*Check the themes too*/
    //lv_test_theme_1(lv_theme_night_init(210, NULL));

    //lv_tutorial_objects();
    //lv_tutorial_antialiasing();
    //lv_tutorial_image();
    //lv_tutorial_styles();
    //lv_tutorial_fonts();
    //lv_tutorial_animations();
    //lv_tutorial_responsive();
    //lv_test_slider_1();
    //lv_test_roller_1();
    //lv_test_mbox_1();
    //lv_test_led_1();
    //lv_test_kb_2();
    //lv_test_chart_1();
    //lv_test_gauge_1();
    //int count = 0;

    //sysmon_create();
    //terminal = terminal_create();
    //terminal_add("hello");
    //lv_test_win_1();
    while(1) {
        /* Periodically call the lv_task handler.
         * It could be done in a timer interrupt or an OS task too.*/
        lv_task_handler();
        usleep(1000);       /*Just to let the system breath*/
        //lv_test_gauge_1_refresh(count++);
        //if (count == 9) count = 0;
    }

    return 0;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

/**
 * Initialize the Hardware Abstraction Layer (HAL) for the Littlev graphics library
 */
static void hal_init(void)
{
    /* Add a display
     * Use the 'monitor' driver which creates window on PC's monitor to simulate a display*/
    monitor_init();
    lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);            /*Basic initialization*/
    disp_drv.disp_flush = monitor_flush;
    disp_drv.disp_fill = monitor_fill;
    disp_drv.disp_map = monitor_map;
    lv_disp_drv_register(&disp_drv);

    /* Add the mouse (or touchpad) as input device
     * Use the 'mouse' driver which reads the PC's mouse*/
    mouse_init();
    lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);          /*Basic initialization*/
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read = mouse_read;         /*This function will be called periodically (by the library) to get the mouse position and state*/
    lv_indev_drv_register(&indev_drv);

    /* Tick init.
     * You have to call 'lv_tick_handler()' in every milliseconds
     * Create an SDL thread to do this*/
    SDL_CreateThread(tick_thread, "tick", NULL);
}

/**
 * A task to measure the elapsed time for LittlevGL
 * @param data unused
 * @return never return
 */
static int tick_thread(void *data)
{
    while(1) {
        lv_tick_inc(1);
        SDL_Delay(1);   /*Sleep for 1 millisecond*/
    }

    return 0;
}

/* A task to periodically change images of 'img_obj' */
static void gif_task(void * img_obj)
{   
    /*Create an array from the images.*/
    static const lv_img_dsc_t * gif_frames[] = {&png_dsc_1, &png_dsc_2, &png_dsc_3, &png_dsc_4, &png_dsc_5, NULL};
    static uint8_t i = 0;
    
    /*Set the current element of the array*/
    lv_img_set_src(img_obj, gif_frames[i]);

    /*Go to the next image*/
    i++;
    if(gif_frames[i] == NULL) i = 0;
}

static void git_load_file(lv_img_dsc_t *img, const char *file_name)
{

    uint32_t error;                 /*For the return values of png decoder functions*/

    /*Load the PNG file into buffer. It's still compressed (not decoded)*/
    unsigned char * png_data;      /*Pointer to the loaded data. Same as the original file just loaded into the RAM*/
    size_t png_data_size;          /*Size of `png_data` in bytes*/

    /*Decode the PNG image*/
    unsigned char * png_decoded;    /*Will be pointer to the decoded image*/
    uint32_t png_width;             /*Will be the width of the decoded image*/
    uint32_t png_height;            /*Will be the width of the decoded image*/

    error = lodepng_load_file(&png_data, &png_data_size, file_name);   /*Load the file*/
    if(error) {
        printf("error %u: %s\n", error, lodepng_error_text(error));
        while(1);
    }

    /*Decode the loaded image in ARGB8888 */
    error = lodepng_decode32(&png_decoded, &png_width, &png_height, png_data, png_data_size);   

    if(error) {
        printf("error %u: %s\n", error, lodepng_error_text(error));
        while(1);
    }

    /*Initialize an image descriptor for LittlevGL with the decoded image*/
    img->header.always_zero = 0;                          /*It must be zero*/
    img->header.cf = LV_IMG_CF_TRUE_COLOR_ALPHA;      /*Set the color format*/
    img->header.w = png_width;
    img->header.h = png_height;
    img->data_size = png_width * png_height * 4;
    img->data = png_decoded;
 
    free(png_data);
}