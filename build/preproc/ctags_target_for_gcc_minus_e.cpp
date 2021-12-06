# 1 "/home/taivv/Documents/TESTOV5640/main.ino"
/**
 * This example takes a picture every 5s and print its size on serial monitor.
 */

// =============================== SETUP ======================================

// 1. Board setup (Uncomment):
// #define BOARD_WROVER_KIT
// #define BOARD_ESP32CAM_AITHINKER

/**
 * 2. Kconfig setup
 * 
 * If you have a Kconfig file, copy the content from
 *  https://github.com/espressif/esp32-camera/blob/master/Kconfig into it.
 * In case you haven't, copy and paste this Kconfig file inside the src directory.
 * This Kconfig file has definitions that allows more control over the camera and
 * how it will be initialized.
 */

/**
 * 3. Enable PSRAM on sdkconfig:
 * 
 * CONFIG_ESP32_SPIRAM_SUPPORT=y
 * 
 * More info on
 * https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/kconfig.html#config-esp32-spiram-support
 */

// ================================ CODE ======================================

# 33 "/home/taivv/Documents/TESTOV5640/main.ino" 2
# 34 "/home/taivv/Documents/TESTOV5640/main.ino" 2
# 35 "/home/taivv/Documents/TESTOV5640/main.ino" 2
# 36 "/home/taivv/Documents/TESTOV5640/main.ino" 2
# 37 "/home/taivv/Documents/TESTOV5640/main.ino" 2

# 39 "/home/taivv/Documents/TESTOV5640/main.ino" 2
# 40 "/home/taivv/Documents/TESTOV5640/main.ino" 2
# 41 "/home/taivv/Documents/TESTOV5640/main.ino" 2

// #define BOARD_WROVER_KIT 1

// // WROVER-KIT PIN Map
// #ifdef BOARD_WROVER_KIT

// #define CAM_PIN_PWDN -1   //power down is not used
// #define CAM_PIN_RESET -1  //software reset will be performed
// #define CAM_PIN_XCLK 21
// #define CAM_PIN_SIOD 26
// #define CAM_PIN_SIOC 27

// #define CAM_PIN_D7 35
// #define CAM_PIN_D6 34
// #define CAM_PIN_D5 39
// #define CAM_PIN_D4 36
// #define CAM_PIN_D3 19
// #define CAM_PIN_D2 18
// #define CAM_PIN_D1 5
// #define CAM_PIN_D0 4
// #define CAM_PIN_VSYNC 25
// #define CAM_PIN_HREF 23
// #define CAM_PIN_PCLK 22

// #endif

// ESP32Cam (AiThinker) PIN Map
// #ifdef BOARD_ESP32CAM_AITHINKER

#define CAM_PIN_PWDN 32
#define CAM_PIN_RESET -1 /*software reset will be performed*/
#define CAM_PIN_XCLK 0
#define CAM_PIN_SIOD 26
#define CAM_PIN_SIOC 27

#define CAM_PIN_D7 35
#define CAM_PIN_D6 34
#define CAM_PIN_D5 39
#define CAM_PIN_D4 36
#define CAM_PIN_D3 21
#define CAM_PIN_D2 19
#define CAM_PIN_D1 18
#define CAM_PIN_D0 5
#define CAM_PIN_VSYNC 25
#define CAM_PIN_HREF 23
#define CAM_PIN_PCLK 22

// #endif

static const char *TAG = "example:take_picture";

static camera_config_t camera_config = {
    .pin_pwdn = 32,
    .pin_reset = -1 /*software reset will be performed*/,
    .pin_xclk = 0,
    .pin_sscb_sda = 26,
    .pin_sscb_scl = 27,

    .pin_d7 = 35,
    .pin_d6 = 34,
    .pin_d5 = 39,
    .pin_d4 = 36,
    .pin_d3 = 21,
    .pin_d2 = 19,
    .pin_d1 = 18,
    .pin_d0 = 5,
    .pin_vsync = 25,
    .pin_href = 23,
    .pin_pclk = 22,

    //XCLK 20MHz or 10MHz for OV2640 double FPS (Experimental)
    .xclk_freq_hz = 20000000,
    .ledc_timer = LEDC_TIMER_0,
    .ledc_channel = LEDC_CHANNEL_0,

    .pixel_format = PIXFORMAT_JPEG, //YUV422,GRAYSCALE,RGB565,JPEG
    .frame_size = FRAMESIZE_QVGA, //QQVGA-UXGA Do not use sizes above QVGA when not JPEG

    .jpeg_quality = 50, //0-63 lower number means higher quality
    .fb_count = 1, //if more than one, i2s runs in continuous mode. Use only with JPEG
                         // .grab_mode = CAMERA_GRAB_WHEN_EMPTY,
};

static esp_err_t init_camera() {
  //initialize the camera
  esp_err_t err = esp_camera_init(&camera_config);
  if (err != 0 /*!< esp_err_t value indicating success (no error) */) {
    log_printf( "[" "E" "][%s:%u] %s(): " "Camera Init Failed" "\r\n", pathToFileName("/home/taivv/Documents/TESTOV5640/main.ino"), 128, __FUNCTION__);
    return err;
  }

  return 0 /*!< esp_err_t value indicating success (no error) */;
}

void setup(void) {
  if (0 /*!< esp_err_t value indicating success (no error) */ != init_camera()) {
    return;
  }
  log_printf( "[" "I" "][%s:%u] %s(): " "Taking picture..." "\r\n", pathToFileName("/home/taivv/Documents/TESTOV5640/main.ino"), 139, __FUNCTION__);
  //   camera_fb_t *pic = esp_camera_fb_get();

  //   // use pic->buf to access the image
  //   ESP_LOGI(TAG, "Picture taken! Its size was: %zu bytes", pic->len);
  //   esp_camera_fb_return(pic);
  camera_fb_t *fb = esp_camera_fb_get();
  if (!fb) {
    log_printf( "[" "E" "][%s:%u] %s(): " "Camera Capture Failed" "\r\n", pathToFileName("/home/taivv/Documents/TESTOV5640/main.ino"), 147, __FUNCTION__);
    log_printf( "[" "I" "][%s:%u] %s(): " "Picture taken! Its size was: %zu bytes" "\r\n", pathToFileName("/home/taivv/Documents/TESTOV5640/main.ino"), 148, __FUNCTION__, fb->len);
    return;
  }
  log_printf( "[" "D" "][%s:%u] %s(): " "Camera Capture" "\r\n", pathToFileName("/home/taivv/Documents/TESTOV5640/main.ino"), 151, __FUNCTION__);
  //replace this with your own function
  //   process_image(fb->width, fb->height, fb->format, fb->buf, fb->len);

  //return the frame buffer back to the driver for reuse
  esp_camera_fb_return(fb);
}
void loop(void) {
    // ESP_LOGI(TAG, "Taking picture...");
    // camera_fb_t *pic = esp_camera_fb_get();
    // // use pic->buf to access the image
    // ESP_LOGI(TAG, "Picture taken! Its size was: %zu bytes", pic->len);
    // esp_camera_fb_return(pic);

    // vTaskDelay(5000 / portTICK_RATE_MS);
}
