
utils = require('utils');

command('block', function (parameters, player) {
    var drone = new Drone(37, 5, 2, 0, utils.world('world'));
    drone.place('152');
});

command('test', function (parameters, player) {
    var theDrone = new Drone(player);
    theDrone.up();
    theDrone.chkpt('start');
    var timeoutStop = new Date().getTime() + 500;
    theDrone.box0('0', 0, 1, 0);
});

var sounds = require('sounds');
function activate_sign(event) {
    //event.getAction() RIGHT_CLICK_BLOCK

    var block = event.getClickedBlock().getType().toString();

    var sneaking = event.getPlayer().isSneaking();
    var action = event.getAction().toString();
    var clicked = event.getClickedBlock().getType().toString();

    //console.log(event.getPlayer().isSneaking());
    //console.log(event.getAction());
    //console.log(event.getClickedBlock().getState());

    var sign = event.getClickedBlock().state;

    if (sneaking && action === 'RIGHT_CLICK_BLOCK' && clicked === 'WALL_SIGN') {
        let module = sign.getLine(0);
        let topic = sign.getLine(1);
        let channel = sign.getLine(2);
        let world = block.getWorld();
        let x = block.getX();
        let y = block.getY();
        let z = block.getZ();
    }

    if (sneaking && action === 'RIGHT_CLICK_BLOCK' && clicked === 'SIGN') {
        let module = sign.getLine(0);
        let topic = sign.getLine(1);
        let channel = sign.getLine(2);
    }

    //var lines = event.getClickedBlock().getLines();

    //var state = event.getClickedBlock().state;

    console.log(event.getClickedBlock().state.getLines());




    //console.log(state);

    //var text = ()

   


    //future activation by an item
    //event.getItem(); //console.log(event.getItem());   
    //event.useItemInHand();

}

events.playerInteract(activate_sign);


//!!!! hub.spigotmc.org/javadocs/spigot/org/bukkit/block/Block.html
//getBlockPower()
//block.isBlockPowered()
//block.isBlockIndirectlyPowered()

