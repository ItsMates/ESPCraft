
utils = require('utils');

command('block', function (parameters, player) {
    var drone = new Drone(37, 5, 2, 0, utils.world('world'));
    drone.box0('152', 1, 1, 1);
});