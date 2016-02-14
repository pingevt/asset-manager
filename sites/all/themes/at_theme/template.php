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
  /*
            Available Classes:

            'enable-cookies'             Remembers active color theme between pages (when set through color theme list)

            'sidebar-l'                  Left Sidebar and right Side Overlay
            'sidebar-r'                  Right Sidebar and left Side Overlay
            'sidebar-mini'               Mini hoverable Sidebar (> 991px)
            'sidebar-o'                  Visible Sidebar by default (> 991px)
            'sidebar-o-xs'               Visible Sidebar by default (< 992px)

            'side-overlay-hover'         Hoverable Side Overlay (> 991px)
            'side-overlay-o'             Visible Side Overlay by default (> 991px)

            'side-scroll'                Enables custom scrolling on Sidebar and Side Overlay instead of native scrolling (> 991px)

            'header-navbar-fixed'        Enables fixed header
            'header-navbar-transparent'  Enables a transparent header (if also fixed, it will get a solid dark background color on scrolling)
  */

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
