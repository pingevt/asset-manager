<?php

define('AT_PATH', '/' . drupal_get_path('theme', 'at_theme'));

/**
 * Implements hook_preprocess_html().
 */
function at_theme_preprocess_html(&$variables) {
  drupal_add_js(AT_PATH . '/js/core/bootstrap.min.js', array('scope' => 'footer'));
  drupal_add_js(AT_PATH . '/js/core/jquery.slimscroll.min.js', array('scope' => 'footer'));
  drupal_add_js(AT_PATH . '/js/core/jquery.scrollLock.min.js', array('scope' => 'footer'));
  drupal_add_js(AT_PATH . '/js/core/jquery.appear.min.js', array('scope' => 'footer'));
  drupal_add_js(AT_PATH . '/js/core/jquery.countTo.min.js', array('scope' => 'footer'));
  drupal_add_js(AT_PATH . '/js/core/jquery.placeholder.min.js', array('scope' => 'footer'));
  drupal_add_js(AT_PATH . '/js/core/js.cookie.min.js', array('scope' => 'footer'));
  //drupal_add_js(AT_PATH . '/js/app.js', array('scope' => 'footer'));
  drupal_add_js(AT_PATH . '/js/plugins/slick/slick.min.js', array('scope' => 'footer'));
  drupal_add_js(AT_PATH . '/js/plugins/chartjs/Chart.min.js', array('scope' => 'footer'));
  //drupal_add_js(AT_PATH . '/js/pages/base_pages_dashboard.js', array('scope' => 'footer'));

}

/**
 * Implements hook_preprocess_page().
 */
function at_theme_preprocess_page(&$vars) {
  global $user;

  $vars['page_classes_array'] = array();
  $vars['page_classes_array'][] = 'enable-cookies';
  $vars['page_classes_array'][] = 'sidebar-l';
  $vars['page_classes_array'][] = 'sidebar-o';
  $vars['page_classes_array'][] = 'side-scroll';
  $vars['page_classes_array'][] = 'header-navbar-fixed';

  // Primary nav.
  $vars['primary_nav'] = FALSE;
  if ($vars['main_menu']) {
    // Build links.
    $vars['primary_nav'] = menu_tree(variable_get('menu_main_links_source', 'main-menu'));
    // Provide default theme wrapper function.
    $vars['primary_nav']['#theme_wrappers'] = array('menu_tree__primary');
  }

  if ($user->uid) {
    $user = user_load($user->uid);
    $vars['user_image'] = theme('image_style', array(
      'style_name' => 'thumbnail',
      'path' => !empty($user->picture->uri)? $user->picture->uri : variable_get('user_picture_default'),
      'attributes' => array(
        'class' => 'avatar',
      )
    ));

    $vars['user_edit_url'] = 'user/' . $user->uid . '/edit';
  }
}

function at_theme_process_page(&$vars) {
  $vars['content_classes'] = implode(' ', $vars['page_classes_array']);
}

/**
 * Bootstrap theme wrapper function for the primary menu links.
 */
function at_theme_menu_tree__primary(&$variables) {
  return '<ul class="nav-main">' . $variables['tree'] . '</ul>';
}

function at_theme_menu_local_tasks(&$variables) {
  $output = '';

  if (!empty($variables['primary'])) {
    $variables['primary']['#prefix'] = '<h2 class="element-invisible">' . t('Primary tabs') . '</h2>';
    $variables['primary']['#prefix'] .= '<div class="block"><ul class="nav nav-tabs nav-tabs-alt">';
    $variables['primary']['#suffix'] = '</ul></div>';
    $output .= drupal_render($variables['primary']);
  }
  if (!empty($variables['secondary'])) {
    $variables['secondary']['#prefix'] = '<h2 class="element-invisible">' . t('Secondary tabs') . '</h2>';
    $variables['secondary']['#prefix'] .= '<div class="block"><ul class="tabs secondary">';
    $variables['secondary']['#suffix'] = '</ul></div>';
    $output .= drupal_render($variables['secondary']);
  }

  return $output;
}

function at_theme_container($variables) {

  $element = $variables['element'];
  // Ensure #attributes is set.
  $element += array('#attributes' => array());

  if (isset($element['#block'])) {
    $element['#attributes']['class'][] = 'block';
    $str = '<div' . drupal_attributes($element['#attributes']) . '>';
    $str .= '<div class="block-header bg-primary">' . $element['#title'] . '</div>';
    $str .= '<div class="block-content">' .  $element['#children'] . '</div></div>';

     return $str;
  }

  // Special handling for form elements.
  if (isset($element['#array_parents'])) {
    // Assign an html ID.
    if (!isset($element['#attributes']['id'])) {
      $element['#attributes']['id'] = $element['#id'];
    }
    // Add the 'form-wrapper' class.
    $element['#attributes']['class'][] = 'form-wrapper';
  }

  return '<div' . drupal_attributes($element['#attributes']) . '>' . $element['#children'] . '</div>';
}

function at_theme_theme($existing, $type, $theme, $path) {
  return array(
    'row' => array(
      'render element' => 'element',
    ),
    'col' => array(
      'render element' => 'element',
    ),
    'toolbar' => array(
      'render element' => 'element',
    ),
    'btn_group' => array(
      'render element' => 'element',
    ),
    '1block' => array(
      'variables' => array(
        'block_header' => NULL,
        'block_header_bg' => NULL,
        'option_items' => array(),
        'rounded' => FALSE,
        'bordered' => FALSE,
        'transparent' => FALSE,
        'themed' => '',
        'children' => array(),
      ),
    ),
  );
}

function at_theme_row(&$vars) {
  $row = $vars['element'];

  $children = element_children($row, TRUE);
  $children_a = '';
  foreach ($children as $key) {
    $children_a .= drupal_render($row[$key]);
  }

  return '<div class="row">' . $children_a . '</div>';
}

function at_theme_col(&$vars) {
  $col = $vars['element'];

  $children = element_children($col, TRUE);
  $children_a = '';
  foreach ($children as $key) {
    $children_a .= drupal_render($col[$key]);
  }

  return '<div ' . drupal_attributes($col['#attributes'])  . '>' . $children_a . '</div>';
}

function at_theme_preprocess_btn_group(&$vars) {
  //$vars['classes_array'][] = 'btn-group';
  $vars['element']['#attributes']['class'][] = 'btn-group';
  $vars['element']['#attributes']['type'] = 'button';
}

function at_theme_process_btn_group(&$vars) {
  //$vars['class'] = implode(' ', $vars['classes_array']);
}

function at_theme_btn_group(&$vars) {
  $el = $vars['element'];

  $children = element_children($el, TRUE);
  $children_a = '';
  foreach ($children as $key) {
    $children_a .= drupal_render($el[$key]);
  }
//dpm($vars);
  $str = '<div ' . drupal_attributes($el['#attributes'])  . '>';
  foreach ($el['#items'] as $item) {
//dpm($item);
    $str .= $item;
  }
  $str .= '</div>' . $children_a;
//dpm($str);
//die();
  return $str;
}

function at_theme_preprocess_toolbar(&$vars) {
  //$vars['classes_array'][] = 'btn-group';
  $vars['element']['#attributes']['class'][] = 'btn-toolbar';
  $vars['element']['#attributes']['roll'] = 'toolbar';
}

function at_theme_process_toolbar(&$vars) {
  //$vars['class'] = implode(' ', $vars['classes_array']);
}

function at_theme_toolbar(&$vars) {
  $el = $vars['element'];

  $children = element_children($el, TRUE);
  $children_a = '';
  foreach ($children as $key) {
    $children_a .= drupal_render($el[$key]);
  }

  return '<div ' . drupal_attributes($el['#attributes'])  . '>' . $children_a . '</div>';
}


function at_theme_preprocess_1block(&$vars) {
  $vars['block_classes_array'] = array('block');
  $vars['block_header_classes_array'] = array('block-header');

  if ($vars['block_header_bg'] != NULL) {
    $vars['block_header_classes_array'][] = $vars['block_header_bg'];
  }

  if ($vars['rounded'] != NULL) {
    $vars['block_classes_array'][] = 'block-rounded';
  }

  if ($vars['bordered'] != NULL) {
    $vars['block_classes_array'][] = 'block-bordered';
  }

  if ($vars['transparent'] != NULL) {
    $vars['block_classes_array'][] = 'block-transparent';
  }

  if (!empty($vars['themed'])) {
    $vars['block_classes_array'][] = 'block-themed';
    $vars['block_header_classes_array'][] = $vars['themed'];
  }
}

function at_theme_process_1block(&$vars) {
  $vars['block_class'] = implode(' ', $vars['block_classes_array']);
  $vars['block_header_class'] = implode(' ', $vars['block_header_classes_array']);
}

function at_theme_1block(&$vars) {

  $str = '<div class="' . $vars['block_class'] . '" >';
  $str .= '<div class="' . $vars['block_header_class'] . '" >';
  if ($vars['option_items'] != NULL) {

  }
  if ($vars['block_header'] != NULL) {
    $str .= '<h3 class="block-title">' . $vars['block_header'] . '</h3>';
  }
  $str .= '</div>';
  $str .= '<div class="block-content">';
  $str .= render($vars['children']);
  $str .= '</div>';
  $str .= '</div>';
  return $str;
}