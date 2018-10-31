'use strict';

var mqtt = require('sc-mqtt');
var utils = require('utils');
var JavaString = java.lang.String;

//=============================== EVENT SETUP ==============================

function sign_activation(event) {

    var sneaking = event.getPlayer().isSneaking();
    var action = event.getAction().toString();
    var clicked = event.getClickedBlock().getType().toString();

    if (sneaking && action === 'RIGHT_CLICK_BLOCK') {

        if (clicked === 'WALL_SIGN') {
            //if (hasItems(event, 'REDSTONE', 1))
            //MQTTNode.prototype.create(event.getClickedBlock().state, true);
            //echo(event.getPlayer(), 'NODE ACTIVATED!');
        }
        else if (clicked === 'SIGN') {
            //if (hasItems(event, 'REDSTONE', 1))       
            MQTTNode.prototype.create(event.getClickedBlock().state, false);
            echo(event.getPlayer(), 'NODE ACTIVATED!');
        }
    }

    
}

events.playerInteract(sign_activation);

//=============================== MQTT NODES ===============================

function MQTTNode(x, y, z, world, topic, playload) { // constructor function

    this.x = x;
    this.y = y;
    this.z = z;
    this.world = utils.world(world);

    this.topic = topic;

    MQTTNode.client.subscribe(topic);

    MQTTNode.count++;
}

// Static variable shared by all instances
MQTTNode.count = 0;
MQTTNode.nodes = [];
MQTTNode.client = mqtt.client('tcp://127.0.0.1:1884', 'MC_SERVER');
MQTTNode.client.connect();

MQTTNode.prototype.create = function (sign, isWallSign) {

    if (!isWallSign) {
        MQTTNode.nodes[MQTTNode.count] = new MQTTNode(sign.getX(), sign.getY() - 1, sign.getZ(), sign.getWorld(), getTopic(sign));
    } else {
        //TO-DO: implement wall sign
    }

    function getTopic(sign) {
        var module_labels =
            [
                ['M1', 'MODULE 1', 'MODULE1', 'TOUCH_MODULE', 'TOUCH MODULE', 'TOU', 'MOD1'],
                ['M2', 'MODULE 2', 'MODULE2', 'PIR_MODULE', 'PIR MODULE', 'PIR', 'MOD2']
            ];

        var topic_labels =
            [
                ['TOU', 'TOUCH', 'T'],
                ['NEO/R', 'NEOPIXEL/RED', 'NEOPIXEL/R', 'NEOPIXEL RED', 'NEOPIXEL R', 'N/R'],
                ['NEO/G', 'NEOPIXEL/GREEN', 'NEOPIXEL/G', 'NEOPIXEL GREEN', 'NEOPIXEL G', 'N/G'],
                ['NEO/B', 'NEOPIXEL/BLUE', 'NEOPIXEL/B', 'NEOPIXEL BLUE', 'NEOPIXEL B', 'N/B'],
                ['REL', 'RELAY', 'R'],
                ['DIS', 'DISPLAY', 'D'],
                ['NEA', 'NEARIR', 'H'],
            ];


        return assemble(decode(sign.getLine(0), module_labels), decode(sign.getLine(1), topic_labels));

        function decode(label, arr) {

            for (var i = 0; i < arr.length; i++) {
                var code = arr[i][0];
                for (var j = 0; j < arr[i].length; j++) {
                    if (label === arr[i][j]) {
                        return code;}
                }
            }
            return '';
        }

        function assemble(module, channel) {        
            return module + '/' + channel;
        }

    }
};

MQTTNode.client.onMessageArrived(function (topic, msg) {
    var message = new JavaString(msg.payload);

    console.log('### MQTT MESSAGE:');
    console.log(topic);
    console.log(message);
    console.log('###');

    for (var i = 0; i < MQTTNode.nodes.length; i++) {
        if (topic === MQTTNode.nodes[i].topic && parseInt(message) > 0) {
            MQTTNode.nodes[i].activate();
        }
        if (topic === MQTTNode.nodes[i].topic && parseInt(message) === 0) {
            MQTTNode.nodes[i].deactivate();
        }
    } 
});

MQTTNode.prototype.activate = function () {
    var drone = new Drone(this.x, this.y, this.z, 0, this.world);
    drone.place('152'); //152 - REDSTONE_BLOCK
};

MQTTNode.prototype.deactivate = function () {
    var drone = new Drone(this.x, this.y, this.z, 0, this.world);
    drone.place('42'); //42 - IRON_BLOCK
};

//// the following callbacks are optional 
//MQTTNode.client.onDeliveryComplete(function (deliveryToken) {
//    // optional callback to handle completion of outgoing messages
//});
//MQTTNode.client.onConnectionLost(function (cause) {
//    // optional callback to handle connection loss
//});

//============================== //MQTT NODES ==============================

command('neo_on', function (parameters, player) {
    echo(player, 'ON');
    MQTTNode.client.publish('M1/NEO/B', '255');
});

command('neo_off', function (parameters, player) {
    echo(player, 'OFF');
    MQTTNode.client.publish('M1/NEO/B', '0');
});





