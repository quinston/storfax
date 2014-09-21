#pragma once

static void click_config_provider(void *context) {
  window_single_repeating_click_subscribe(BUTTON_ID_SELECT, 30, select_click_handler);
  window_single_repeating_click_subscribe(BUTTON_ID_UP,30, up_click_handler);
  window_single_repeating_click_subscribe(BUTTON_ID_DOWN, 30, down_click_handler);
}
