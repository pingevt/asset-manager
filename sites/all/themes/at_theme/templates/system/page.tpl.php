<?php

/**
 * @file
 * Default theme implementation to display a single Drupal page.
 *
 * The doctype, html, head and body tags are not in this template. Instead they
 * can be found in the html.tpl.php template in this directory.
 *
 * Available variables:
 *
 * General utility variables:
 * - $base_path: The base URL path of the Drupal installation. At the very
 *   least, this will always default to /.
 * - $directory: The directory the template is located in, e.g. modules/system
 *   or themes/bartik.
 * - $is_front: TRUE if the current page is the front page.
 * - $logged_in: TRUE if the user is registered and signed in.
 * - $is_admin: TRUE if the user has permission to access administration pages.
 *
 * Site identity:
 * - $front_page: The URL of the front page. Use this instead of $base_path,
 *   when linking to the front page. This includes the language domain or
 *   prefix.
 * - $logo: The path to the logo image, as defined in theme configuration.
 * - $site_name: The name of the site, empty when display has been disabled
 *   in theme settings.
 * - $site_slogan: The slogan of the site, empty when display has been disabled
 *   in theme settings.
 *
 * Navigation:
 * - $main_menu (array): An array containing the Main menu links for the
 *   site, if they have been configured.
 * - $secondary_menu (array): An array containing the Secondary menu links for
 *   the site, if they have been configured.
 * - $breadcrumb: The breadcrumb trail for the current page.
 *
 * Page content (in order of occurrence in the default page.tpl.php):
 * - $title_prefix (array): An array containing additional output populated by
 *   modules, intended to be displayed in front of the main title tag that
 *   appears in the template.
 * - $title: The page title, for use in the actual HTML content.
 * - $title_suffix (array): An array containing additional output populated by
 *   modules, intended to be displayed after the main title tag that appears in
 *   the template.
 * - $messages: HTML for status and error messages. Should be displayed
 *   prominently.
 * - $tabs (array): Tabs linking to any sub-pages beneath the current page
 *   (e.g., the view and edit tabs when displaying a node).
 * - $action_links (array): Actions local to the page, such as 'Add menu' on the
 *   menu administration interface.
 * - $feed_icons: A string of all feed icons for the current page.
 * - $node: The node object, if there is an automatically-loaded node
 *   associated with the page, and the node ID is the second argument
 *   in the page's path (e.g. node/12345 and node/12345/revisions, but not
 *   comment/reply/12345).
 *
 * Regions:
 * - $page['help']: Dynamic help text, mostly for admin pages.
 * - $page['highlighted']: Items for the highlighted content region.
 * - $page['content']: The main content of the current page.
 * - $page['sidebar_first']: Items for the first sidebar.
 * - $page['sidebar_second']: Items for the second sidebar.
 * - $page['header']: Items for the header region.
 * - $page['footer']: Items for the footer region.
 *
 * @see template_preprocess()
 * @see template_preprocess_page()
 * @see template_process()
 * @see html.tpl.php
 *
 * @ingroup themeable
 */
?>

    <div id="page-container" class="<?php print $content_classes; ?>">

        <?php if ($page['sidebar_second']): ?>
          <!-- Side Overlay-->
          <aside id="side-overlay">
              <!-- Side Overlay Scroll Container -->
              <div id="side-overlay-scroll">
                  <!-- Side Header -->
                  <div class="side-header side-content">
                    <button class="btn btn-default pull-right" type="button" data-toggle="layout" data-action="side_overlay_close">
                        <i class="fa fa-times"></i>
                    </button>
                  </div>
                  <!-- END Side Header -->

                  <!-- Side Content -->
                  <div class="side-content remove-padding-t">
                      <!-- Side Overlay Tabs -->

                      <div id="sidebar-second" class="column sidebar"><div class="section">
                        <?php print render($page['sidebar_second']); ?>
                      </div></div> <!~~ /.section, /#sidebar-second ~~>

                      <!-- END Side Overlay Tabs -->
                  </div>
                  <!-- END Side Content -->
              </div>
              <!-- END Side Overlay Scroll Container -->
          </aside>
          <!-- END Side Overlay -->
        <?php endif; ?>

        <!-- Sidebar -->
        <nav id="sidebar">
            <!-- Sidebar Scroll Container -->
            <div id="sidebar-scroll">
                <!-- Sidebar Content -->
                <!-- Adding .sidebar-mini-hide to an element will hide it when the sidebar is in mini mode -->
                <div class="sidebar-content">
                    <!-- Side Header -->
                    <div class="side-header side-content bg-white-op">
                        <!-- Layout API, functionality initialized in App() -> uiLayoutApi() -->
                        <button class="btn btn-link text-gray pull-right hidden-md hidden-lg" type="button" data-toggle="layout" data-action="sidebar_close">
                            <i class="fa fa-times"></i>
                        </button>
                        <a class="h5 text-white" href="/">
                            <span class="h4 font-w600 sidebar-mini-hide">ATManager</span>
                        </a>
                    </div>
                    <!-- END Side Header -->

                    <!-- Side Content -->
                    <div class="side-content">
                        <?php if (!empty($primary_nav)): ?>
                          <?php print render($primary_nav); ?>
                        <?php endif; ?>
                    <!--
                        <ul class="nav-main">
                            <li>
                                <a class="active" href="index.html"><i class="si si-speedometer"></i><span class="sidebar-mini-hide">Dashboard</span></a>
                            </li>
                            <li class="nav-main-heading"><span class="sidebar-mini-hide">User Interface</span></li>
                            <li>
                                <a class="nav-submenu" data-toggle="nav-submenu" href="#"><i class="si si-badge"></i><span class="sidebar-mini-hide">UI Elements</span></a>
                                <ul>
                                    <li>
                                        <a href="base_ui_widgets.html">Widgets</a>
                                    </li>
                                    <li>
                                        <a class="nav-submenu" data-toggle="nav-submenu" href="#">Blocks</a>
                                        <ul>
                                            <li>
                                                <a href="base_ui_blocks.html">Styles</a>
                                            </li>
                                            <li>
                                                <a href="base_ui_blocks_api.html">Blocks API</a>
                                            </li>
                                            <li>
                                                <a href="base_ui_blocks_draggable.html">Draggable</a>
                                            </li>
                                        </ul>
                                    </li>
                                    <li>
                                        <a href="base_ui_grid.html">Grid</a>
                                    </li>
                                    <li>
                                        <a href="base_ui_typography.html">Typography</a>
                                    </li>
                                    <li>
                                        <a href="base_ui_icons.html">Icons</a>
                                    </li>
                                    <li>
                                        <a href="base_ui_buttons.html">Buttons</a>
                                    </li>
                                    <li>
                                        <a href="base_ui_activity.html">Activity</a>
                                    </li>
                                    <li>
                                        <a href="base_ui_tabs.html">Tabs</a>
                                    </li>
                                    <li>
                                        <a href="base_ui_tiles.html">Tiles</a>
                                    </li>
                                    <li>
                                        <a href="base_ui_ribbons.html">Ribbons</a>
                                    </li>
                                    <li>
                                        <a class="nav-submenu" data-toggle="nav-submenu" href="#">Chat</a>
                                        <ul>
                                            <li>
                                                <a href="base_ui_chat_full.html">Full</a>
                                            </li>
                                            <li>
                                                <a href="base_ui_chat_fixed.html">Fixed</a>
                                            </li>
                                            <li>
                                                <a href="base_ui_chat_popup.html">Popup</a>
                                            </li>
                                        </ul>
                                    </li>
                                    <li>
                                        <a class="nav-submenu" data-toggle="nav-submenu" href="#">Timeline</a>
                                        <ul>
                                            <li>
                                                <a href="base_ui_timeline.html">Various</a>
                                            </li>
                                            <li>
                                                <a href="base_ui_timeline_social.html">Social</a>
                                            </li>
                                        </ul>
                                    </li>
                                    <li>
                                        <a href="base_ui_navigation.html">Navigation</a>
                                    </li>
                                    <li>
                                        <a href="base_ui_modals_tooltips.html">Modals &amp; Tooltips</a>
                                    </li>
                                    <li>
                                        <a href="base_ui_color_themes.html">Color Themes</a>
                                    </li>
                                </ul>
                            </li>
                            <li>
                                <a class="nav-submenu" data-toggle="nav-submenu" href="#"><i class="si si-grid"></i><span class="sidebar-mini-hide">Tables</span></a>
                                <ul>
                                    <li>
                                        <a href="base_tables_styles.html">Styles</a>
                                    </li>
                                    <li>
                                        <a href="base_tables_responsive.html">Responsive</a>
                                    </li>
                                    <li>
                                        <a href="base_tables_tools.html">Tools</a>
                                    </li>
                                    <li>
                                        <a href="base_tables_pricing.html">Pricing</a>
                                    </li>
                                    <li>
                                        <a href="base_tables_datatables.html">DataTables</a>
                                    </li>
                                </ul>
                            </li>
                            <li>
                                <a class="nav-submenu" data-toggle="nav-submenu" href="#"><i class="si si-note"></i><span class="sidebar-mini-hide">Forms</span></a>
                                <ul>
                                    <li>
                                        <a href="base_forms_premade.html">Pre-made</a>
                                    </li>
                                    <li>
                                        <a href="base_forms_elements.html">Elements</a>
                                    </li>
                                    <li>
                                        <a href="base_forms_pickers_more.html">Pickers &amp; More</a>
                                    </li>
                                    <li>
                                        <a href="base_forms_editors.html">Text Editors</a>
                                    </li>
                                    <li>
                                        <a href="base_forms_validation.html">Validation</a>
                                    </li>
                                    <li>
                                        <a href="base_forms_wizard.html">Wizard</a>
                                    </li>
                                </ul>
                            </li>
                            <li class="nav-main-heading"><span class="sidebar-mini-hide">Develop</span></li>
                            <li>
                                <a class="nav-submenu" data-toggle="nav-submenu" href="#"><i class="si si-wrench"></i><span class="sidebar-mini-hide">Components</span></a>
                                <ul>
                                    <li>
                                        <a href="base_comp_images.html">Images</a>
                                    </li>
                                    <li>
                                        <a href="base_comp_charts.html">Charts</a>
                                    </li>
                                    <li>
                                        <a href="base_comp_calendar.html">Calendar</a>
                                    </li>
                                    <li>
                                        <a href="base_comp_sliders.html">Sliders</a>
                                    </li>
                                    <li>
                                        <a href="base_comp_animations.html">Animations</a>
                                    </li>
                                    <li>
                                        <a href="base_comp_scrolling.html">Scrolling</a>
                                    </li>
                                    <li>
                                        <a href="base_comp_syntax_highlighting.html">Syntax Highlighting</a>
                                    </li>
                                    <li>
                                        <a href="base_comp_rating.html">Rating</a>
                                    </li>
                                    <li>
                                        <a href="base_comp_treeview.html">Tree View</a>
                                    </li>
                                    <li>
                                        <a class="nav-submenu" data-toggle="nav-submenu" href="#">Maps</a>
                                        <ul>
                                            <li>
                                                <a href="base_comp_maps.html">Google</a>
                                            </li>
                                            <li>
                                                <a href="base_comp_maps_full.html">Google Full</a>
                                            </li>
                                            <li>
                                                <a href="base_comp_maps_vector.html">Vector</a>
                                            </li>
                                        </ul>
                                    </li>
                                    <li>
                                        <a class="nav-submenu" data-toggle="nav-submenu" href="#">Gallery</a>
                                        <ul>
                                            <li>
                                                <a href="base_comp_gallery_simple.html">Simple</a>
                                            </li>
                                            <li>
                                                <a href="base_comp_gallery_advanced.html">Advanced</a>
                                            </li>
                                        </ul>
                                    </li>
                                </ul>
                            </li>
                            <li>
                                <a class="nav-submenu" data-toggle="nav-submenu" href="#"><i class="si si-magic-wand"></i><span class="sidebar-mini-hide">Layouts</span></a>
                                <ul>
                                    <li>
                                        <a href="base_layouts_api.html">Layout API</a>
                                    </li>
                                    <li>
                                        <a href="base_layouts_default.html">Default</a>
                                    </li>
                                    <li>
                                        <a href="base_layouts_default_flipped.html">Default Flipped</a>
                                    </li>
                                    <li>
                                        <a href="base_layouts_header_static.html">Static Header</a>
                                    </li>
                                    <li>
                                        <a href="base_layouts_sidebar_mini_hoverable.html">Mini Sidebar (Hoverable)</a>
                                    </li>
                                    <li>
                                        <a href="base_layouts_side_overlay_hoverable.html">Side Overlay (Hoverable)</a>
                                    </li>
                                    <li>
                                        <a href="base_layouts_side_overlay_open.html">Side Overlay (Open)</a>
                                    </li>
                                    <li>
                                        <a href="base_layouts_side_native_scrolling.html">Side Native Scrolling</a>
                                    </li>
                                    <li>
                                        <a href="base_layouts_sidebar_hidden.html">Hidden Sidebar</a>
                                    </li>
                                </ul>
                            </li>
                            <li>
                                <a class="nav-submenu" data-toggle="nav-submenu" href="#"><i class="si si-puzzle"></i><span class="sidebar-mini-hide">Multi Level Menu</span></a>
                                <ul>
                                    <li>
                                        <a href="#">Link 1-1</a>
                                    </li>
                                    <li>
                                        <a href="#">Link 1-2</a>
                                    </li>
                                    <li>
                                        <a class="nav-submenu" data-toggle="nav-submenu" href="#">Sub Level 2</a>
                                        <ul>
                                            <li>
                                                <a href="#">Link 2-1</a>
                                            </li>
                                            <li>
                                                <a href="#">Link 2-2</a>
                                            </li>
                                            <li>
                                                <a class="nav-submenu" data-toggle="nav-submenu" href="#">Sub Level 3</a>
                                                <ul>
                                                    <li>
                                                        <a href="#">Link 3-1</a>
                                                    </li>
                                                    <li>
                                                        <a href="#">Link 3-2</a>
                                                    </li>
                                                    <li>
                                                        <a class="nav-submenu" data-toggle="nav-submenu" href="#">Sub Level 4</a>
                                                        <ul>
                                                            <li>
                                                                <a href="#">Link 4-1</a>
                                                            </li>
                                                            <li>
                                                                <a href="#">Link 4-2</a>
                                                            </li>
                                                            <li>
                                                                <a class="nav-submenu" data-toggle="nav-submenu" href="#">Sub Level 5</a>
                                                                <ul>
                                                                    <li>
                                                                        <a href="#">Link 5-1</a>
                                                                    </li>
                                                                    <li>
                                                                        <a href="#">Link 5-2</a>
                                                                    </li>
                                                                    <li>
                                                                        <a class="nav-submenu" data-toggle="nav-submenu" href="#">Sub Level 6</a>
                                                                        <ul>
                                                                            <li>
                                                                                <a href="#">Link 6-1</a>
                                                                            </li>
                                                                            <li>
                                                                                <a href="#">Link 6-2</a>
                                                                            </li>
                                                                        </ul>
                                                                    </li>
                                                                </ul>
                                                            </li>
                                                        </ul>
                                                    </li>
                                                </ul>
                                            </li>
                                        </ul>
                                    </li>
                                </ul>
                            </li>
                            <li class="nav-main-heading"><span class="sidebar-mini-hide">Pages</span></li>
                            <li>
                                <a class="nav-submenu" data-toggle="nav-submenu" href="#"><i class="si si-layers"></i><span class="sidebar-mini-hide">Generic</span></a>
                                <ul>
                                    <li>
                                        <a href="base_pages_blank.html">Blank</a>
                                    </li>
                                    <li>
                                        <a href="base_pages_search.html">Search Results</a>
                                    </li>
                                    <li>
                                        <a href="base_pages_invoice.html">Invoice</a>
                                    </li>
                                    <li>
                                        <a href="base_pages_faq.html">FAQ</a>
                                    </li>
                                    <li>
                                        <a href="base_pages_inbox.html">Inbox</a>
                                    </li>
                                    <li>
                                        <a class="nav-submenu" data-toggle="nav-submenu" href="#">User Profile</a>
                                        <ul>
                                            <li>
                                                <a href="base_pages_profile.html">Profile</a>
                                            </li>
                                            <li>
                                                <a href="base_pages_profile_v2.html">Profile v2</a>
                                            </li>
                                            <li>
                                                <a href="base_pages_profile_edit.html">Profile Edit</a>
                                            </li>
                                        </ul>
                                    </li>
                                    <li>
                                        <a class="nav-submenu" data-toggle="nav-submenu" href="#">Forum</a>
                                        <ul>
                                            <li>
                                                <a href="base_pages_forum_categories.html">Categories</a>
                                            </li>
                                            <li>
                                                <a href="base_pages_forum_topics.html">Topics</a>
                                            </li>
                                            <li>
                                                <a href="base_pages_forum_discussion.html">Discussion</a>
                                            </li>
                                            <li>
                                                <a href="base_pages_forum_new_topic.html">New Topic</a>
                                            </li>
                                        </ul>
                                    </li>
                                    <li>
                                        <a class="nav-submenu" data-toggle="nav-submenu" href="#">Authentication</a>
                                        <ul>
                                            <li>
                                                <a href="base_pages_login.html">Log In</a>
                                            </li>
                                            <li>
                                                <a href="base_pages_login_v2.html">Log In v2</a>
                                            </li>
                                            <li>
                                                <a href="base_pages_register.html">Register</a>
                                            </li>
                                            <li>
                                                <a href="base_pages_register_v2.html">Register v2</a>
                                            </li>
                                            <li>
                                                <a href="base_pages_lock.html">Lock Screen</a>
                                            </li>
                                            <li>
                                                <a href="base_pages_lock_v2.html">Lock Screen v2</a>
                                            </li>
                                            <li>
                                                <a href="base_pages_reminder.html">Password Reminder</a>
                                            </li>
                                            <li>
                                                <a href="base_pages_reminder_v2.html">Password Reminder v2</a>
                                            </li>
                                        </ul>
                                    </li>
                                    <li>
                                        <a href="base_pages_coming_soon.html">Coming Soon</a>
                                    </li>
                                    <li>
                                        <a href="base_pages_maintenance.html">Maintenance</a>
                                    </li>
                                </ul>
                            </li>
                            <li>
                                <a class="nav-submenu" data-toggle="nav-submenu" href="#"><i class="si si-bag"></i><span class="sidebar-mini-hide">e-Commerce</span></a>
                                <ul>
                                    <li>
                                        <a href="base_pages_ecom_dashboard.html">Dashboard</a>
                                    </li>
                                    <li>
                                        <a href="base_pages_ecom_orders.html">Orders</a>
                                    </li>
                                    <li>
                                        <a href="base_pages_ecom_order.html">Order</a>
                                    </li>
                                    <li>
                                        <a href="base_pages_ecom_products.html">Products</a>
                                    </li>
                                    <li>
                                        <a href="base_pages_ecom_product_edit.html">Product Edit</a>
                                    </li>
                                    <li>
                                        <a href="base_pages_ecom_customer.html">Customer</a>
                                    </li>
                                </ul>
                            </li>
                            <li>
                                <a class="nav-submenu" data-toggle="nav-submenu" href="#"><i class="si si-fire"></i><span class="sidebar-mini-hide">Error Pages</span></a>
                                <ul>
                                    <li>
                                        <a href="base_pages_400.html">400</a>
                                    </li>
                                    <li>
                                        <a href="base_pages_401.html">401</a>
                                    </li>
                                    <li>
                                        <a href="base_pages_403.html">403</a>
                                    </li>
                                    <li>
                                        <a href="base_pages_404.html">404</a>
                                    </li>
                                    <li>
                                        <a href="base_pages_500.html">500</a>
                                    </li>
                                    <li>
                                        <a href="base_pages_503.html">503</a>
                                    </li>
                                </ul>
                            </li>
                            <li class="nav-main-heading"><span class="sidebar-mini-hide">Apps</span></li>
                            <li>
                                <a href="frontend_home.html"><i class="si si-rocket"></i><span class="sidebar-mini-hide">Frontend</span></a>
                            </li>
                        </ul>
                        -->
                    </div>
                    <!-- END Side Content -->
                </div>
                <!-- Sidebar Content -->
            </div>
            <!-- END Sidebar Scroll Container -->
        </nav>
        <!-- END Sidebar -->

        <!-- Header -->
        <header id="header-navbar" class="content-mini content-mini-full">
            <!-- Header Navigation Right -->
            <ul class="nav-header pull-right">
                <li>
                    <div class="btn-group">
                        <button class="btn btn-default btn-image dropdown-toggle" data-toggle="dropdown" type="button">
                            <?php print $user_image; ?>
                            <span class="caret"></span>
                        </button>
                        <ul class="dropdown-menu dropdown-menu-right">
                            <li class="dropdown-header">Profile</li>
                            <li>
                                <a tabindex="-1" href="<?php print $user_edit_url; ?>">
                                    <i class="si si-settings pull-right"></i>Settings
                                </a>
                            </li>
                            <li>
                                <a tabindex="-1" href="base_pages_login.html">
                                    <i class="si si-logout pull-right"></i>Log out
                                </a>
                            </li>
                        </ul>
                    </div>
                </li>
                <?php if ($page['sidebar_second']): ?>
                <li>
                    <!-- Layout API, functionality initialized in App() -> uiLayoutApi() -->
                    <button class="btn btn-default" data-toggle="layout" data-action="side_overlay_toggle" type="button">
                        <i class="fa fa-tasks"></i>
                    </button>
                </li>
                <?php endif; ?>
            </ul>
            <!-- END Header Navigation Right -->

<!--
            <ul class="nav-header pull-left">
                <li class="hidden-md hidden-lg">
                    <!~~ Layout API, functionality initialized in App() -> uiLayoutApi() ~~>
                    <button class="btn btn-default" data-toggle="layout" data-action="sidebar_toggle" type="button">
                        <i class="fa fa-navicon"></i>
                    </button>
                </li>
                <li class="hidden-xs hidden-sm">
                    <!~~ Layout API, functionality initialized in App() -> uiLayoutApi() ~~>
                    <button class="btn btn-default" data-toggle="layout" data-action="sidebar_mini_toggle" type="button">
                        <i class="fa fa-ellipsis-v"></i>
                    </button>
                </li>
            </ul>
 -->
        </header>
        <!-- END Header -->

        <!-- Main Container -->
        <main id="main-container">

            <?php if ($messages): ?>
              <div class="content bg-white border-b"><?php print $messages; ?></div>
            <?php endif; ?>

            <div class="content">
              <?php if ($page['highlighted']): ?><div id="highlighted"><?php print render($page['highlighted']); ?></div><?php endif; ?>
              <a id="main-content"></a>
              <?php print render($title_prefix); ?>
              <?php if ($title): ?><h1 class="title" id="page-title"><?php print $title; ?></h1><?php endif; ?>
              <?php print render($title_suffix); ?>
              <?php if ($tabs): ?><div class="tabs"><?php print render($tabs); ?></div><?php endif; ?>
              <?php if ($action_links): ?><ul class="action-links"><?php print render($action_links); ?></ul><?php endif; ?>
              <?php print render($page['content']); ?>
            </div>
        </main>
        <!-- END Main Container -->

        <!-- Footer -->
        <footer id="page-footer" class="content-mini content-mini-full font-s12 bg-gray-lighter clearfix">
            <?php print render($page['footer']); ?>
        </footer>
        <!-- END Footer -->
    </div>
    <!-- END Page Container -->
