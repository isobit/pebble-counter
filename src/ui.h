static Window *parent_window;
static TextLayer *count_text_layer;
static void ui_load(void) {
parent_window = window_create();
window_set_background_color(parent_window,GColorBlack);
count_text_layer = text_layer_create((GRect){.origin={0,50},.size={(int)layer_get_frame(window_get_root_layer(parent_window)).size.w * ((float)100 / 100),50}});
text_layer_set_font(count_text_layer,fonts_get_system_font(FONT_KEY_BITHAM_42_MEDIUM_NUMBERS));
text_layer_set_text_color(count_text_layer,GColorWhite);
text_layer_set_text_alignment(count_text_layer,GTextAlignmentCenter);
text_layer_set_background_color(count_text_layer,GColorBlack);
layer_add_child(window_get_root_layer(parent_window), text_layer_get_layer(count_text_layer));
}
static void ui_unload(void) {
window_destroy(parent_window);
text_layer_destroy(count_text_layer);
}