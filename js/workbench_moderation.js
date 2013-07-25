/**
 * @file
 * Sets the summary for Workbench moderation on vertical tabs.
 */

(function ($) {

Drupal.behaviors.workbenchModerationSettingsSummary = {
  attach: function(context) {

    // Set summary for the revisions information tab to use the event select
    // list.
    $('fieldset.node-form-revision-information', context).drupalSetSummary(function (context) {
      var vals = [];

      // @todo, "event" is too generic of a name and might change in the future.
      if ($('select[name="event"]', context).val()) {
        vals.push(Drupal.checkPlain($('select[name="event"] option:selected').text()));
      }
      return vals.join(', ');
    });

    // Override the summary for what core calls publishing options.
    $('fieldset.node-form-options', context).drupalSetSummary(function (context) {
      var vals = [];

      $('input:checked', context).parent().each(function () {
        vals.push(Drupal.checkPlain($.trim($(this).text())));
      });
      return vals.join(', ');
    });
  }
};

})(jQuery);
