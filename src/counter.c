#include <pebble.h>
#include <ui.h>

#define COUNT_PKEY 1
#define COUNT_DEFAULT 0
static int count= COUNT_DEFAULT;

static void update() {
    static char count_text[100];
    snprintf(count_text, sizeof(count_text), "%i", count);
    text_layer_set_text(count_text_layer, count_text);
}

static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
    count = 0;
    update();
}

static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
    count++;
    update();
}

static void down_click_handler(ClickRecognizerRef recognizer, void *context) {
    count--;
    update();
}

static void select_click_handler_long(ClickRecognizerRef recognizer, void *context) {
    count = 20;
    update();
}

static void up_click_handler_long(ClickRecognizerRef recognizer, void *context) {
    count += 5;
    update();
}

static void down_click_handler_long(ClickRecognizerRef recognizer, void *context) {
    count -= 5;
    update();
}

static void click_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
  window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
  int ms_long_delay = 0;
  window_long_click_subscribe(BUTTON_ID_SELECT, ms_long_delay, select_click_handler_long, NULL);
  window_long_click_subscribe(BUTTON_ID_UP, ms_long_delay, up_click_handler_long, NULL);
  window_long_click_subscribe(BUTTON_ID_DOWN, ms_long_delay, down_click_handler_long, NULL);
}

static void init(void) {
    count = persist_exists(COUNT_PKEY) ? persist_read_int(COUNT_PKEY) : COUNT_DEFAULT;
    ui_load();
    update();
    window_set_click_config_provider(parent_window, click_config_provider);
    window_stack_push(parent_window, true);
}

static void deinit(void) {
    persist_write_int(COUNT_PKEY, count);
    ui_unload();
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}
