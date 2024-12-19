<?php
/**
 * @file
 * Handles all form alters and submit functions for entityconnect.
 */

/**
 * Defines the settings form.
 */
function _entityconnect_admin_form($form, &$form_state) {
  $config = config('entityconnect.settings');
  $form = array();

  $form['entityconnect'] = array(
    '#type' => 'fieldset',
    '#title' => t('EntityConnect default Parameters'),
  );

  $form['entityconnect']['cache_lifetime'] = array(
    '#default_value' => $config->get('entityconnect_cache_lifetime'),
    '#description' => t('Set cache lifetime in second.<br />
                        Set to 0 to CACHE_PERMANENT.'),
    '#weight' => '0',
    '#type' => 'number',
    '#title' => t('Entity Connect cache lifetime'),
  );


  $form['entityconnect']['button'] = array(
    '#type' => 'fieldset',
    '#title' => t('Buttons display Parameters'),
  );

  $form['entityconnect']['button']['button_add'] = array(
    '#required' => '1',
    '#key_type_toggled' => '1',
    '#default_value' => $config->get('entityconnect_unload_add_default'),
    '#description' => t('Default: "off"<br />
                          Choose "on" if you want the "add" buttons displayed by default.<br />
                          Each field can override this value.'),
    '#weight' => '0',
    '#type' => 'radios',
    '#options' => array(
      '0' => t('on'),
      '1' => t('off'),
    ),
    '#title' => t('Default Entity Connect "add" button display'),
  );

  $form['entityconnect']['button']['button_edit'] = array(
    '#required' => '1',
    '#key_type_toggled' => '1',
    '#default_value' => $config->get('entityconnect_unload_edit_default'),
    '#description' => t('Default: "off"<br />
      Choose "on" if you want the "edit" buttons displayed by default.<br />
      Each field can override this value.'),
    '#weight' => '1',
    '#type' => 'radios',
    '#options' => array(
      '0' => t('on'),
      '1' => t('off'),
    ),
    '#title' => t('Default Entity Connect "edit" button display'),
  );

  $form['entityconnect']['icon'] = array(
    '#type' => 'fieldset',
    '#title' => t('Icons display Parameters'),
  );

  $form['entityconnect']['icon']['icon_add'] = array(
    '#required' => '1',
    '#key_type_toggled' => '1',
    '#default_value' => $config->get('entityconnect_show_add_icon_default'),
    '#description' => t('Default: "Icon only"<br />
      Choose "Icon + Text" if you want to see the edit (pencil) icon + the text displayed by default.<br />
      Choose "Text only" if you don\'t want to see the edit (pencil) icon displayed by default.<br />
      Each field can override this value.'),
    '#weight' => '2',
    '#type' => 'radios',
    '#options' => array(
      '0' => t('Icon only'),
      '1' => t('Icon + Text'),
      '2' => t('Text only')
    ),
    '#title' => t('Default Entity Connect "add (+) icon" display'),
  );

  $form['entityconnect']['icon']['icon_edit'] = array(
    '#required' => '1',
    '#key_type_toggled' => '1',
    '#default_value' => $config->get('entityconnect_show_edit_icon_default'),
    '#description' => t('Default: "Icon only"<br />
      Choose "Icon + Text" if you want to see the edit (pencil) icon + the text displayed by default.<br />
      Choose "Text only" if you don\'t want to see the edit (pencil) icon displayed by default.<br />
      Each field can override this value.'),
    '#weight' => '3',
    '#type' => 'radios',
    '#options' => array(
      '0' => t('Icon only'),
      '1' => t('Icon + Text'),
      '2' => t('Text only')
    ),
    '#title' => t('Default Entity Connect "edit (pencil) icon" display'),
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Save',
    '#weight' => '2',
  );

  $form['reset'] = array(
    '#type' => 'submit',
    '#value' => 'Reset to default',
    '#weight' => '3',
  );

  return $form;
}

/**
 * The settings form submit.
 */
function _entityconnect_admin_form_submit($form, &$form_state) {
  if ($form_state['clicked_button']['#id'] == 'edit-reset') {
    config_set('entityconnect.settings', 'entityconnect_cache_lifetime', CACHE_PERMANENT);
    config_set('entityconnect.settings', 'entityconnect_unload_add_default', 1);
    config_set('entityconnect.settings', 'entityconnect_unload_edit_default', 1);
    config_set('entityconnect.settings', 'entityconnect_show_add_icon_default', 0);
    config_set('entityconnect.settings', 'entityconnect_show_edit_icon_default', 0);
    backdrop_set_message(t('The settings were reset to default.'));
  }
  else {
    config_set('entityconnect.settings', 'entityconnect_cache_lifetime', $form_state['values']['cache_lifetime']);
    config_set('entityconnect.settings', 'entityconnect_unload_add_default', $form_state['values']['button_add']);
    config_set('entityconnect.settings', 'entityconnect_unload_edit_default', $form_state['values']['button_edit']);
    config_set('entityconnect.settings', 'entityconnect_show_add_icon_default', $form_state['values']['icon_add']);
    config_set('entityconnect.settings', 'entityconnect_show_edit_icon_default', $form_state['values']['icon_edit']);
    backdrop_set_message(t('The settings were saved.'));
  }
}
