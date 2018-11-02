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
            //echo(event.getPlayer(), 'NODE ACTIVATED!');
            //MQTTNode.prototype.create(event.getClickedBlock().state, true);
        }
        else if (clicked === 'SIGN') {
            //if (hasItems(event, 'REDSTONE', 1))    
            echo(event.getPlayer(), 'Receiver ACTIVATED!');
            MQTTReceiver.prototype.create(event.getClickedBlock().state, false);

            //echo(event.getPlayer(), 'Sender ACTIVATED!');
            //MQTTSender.prototype.create(event.getClickedBlock().state, false);

        }
    }
}

events.playerInteract(sign_activation);

//=============================== TOPIC DECODING ===============================

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
                    return code;
                }
            }
        }
        return '';
    }

    function assemble(module, channel) {
        return module + '/' + channel;
    }

}

//=============================== //TOPIC DECODING ===============================


//=============================== MQTT NODES ===============================

function MQTTReceiver(x, y, z, world, topic, payload) { // constructor function

    this.x = x;
    this.y = y;
    this.z = z;
    this.world = utils.world(world);

    this.topic = topic;

    MQTTReceiver.client.subscribe(topic);

    MQTTReceiver.count++;
}

// Static variable shared by all instances
MQTTReceiver.count = 0;
MQTTReceiver.nodes = [];
MQTTReceiver.client = mqtt.client('tcp://127.0.0.1:1884', 'MC_SERVER');
MQTTReceiver.client.connect();

MQTTReceiver.prototype.create = function (sign, isWallSign) {

    if (!isWallSign) {
        MQTTReceiver.nodes[MQTTReceiver.count] = new MQTTReceiver(sign.getX(), sign.getY() - 1, sign.getZ(), sign.getWorld(), getTopic(sign));
    } else {
        //TO-DO: implement wall sign
    }
};

MQTTReceiver.client.onMessageArrived(function (topic, msg) {
    var message = new JavaString(msg.payload);

    console.log('### MQTT MESSAGE:');
    console.log(topic);
    console.log(message);
    console.log('###');

    for (var i = 0; i < MQTTReceiver.nodes.length; i++) {
        if (topic === MQTTReceiver.nodes[i].topic && parseInt(message) > 0) {
            MQTTReceiver.nodes[i].activate();
        }
        if (topic === MQTTReceiver.nodes[i].topic && parseInt(message) === 0) {
            MQTTReceiver.nodes[i].deactivate();
        }
    }
});

MQTTReceiver.prototype.activate = function () {
    var drone = new Drone(this.x, this.y, this.z, 0, this.world);
    drone.place('152'); //152 - REDSTONE_BLOCK
};

MQTTReceiver.prototype.deactivate = function () {
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


//============================== //MQTT SENDER ==============================


function MQTTSender(x, y, z, world, topic, payload) { // constructor function

    this.x = x;
    this.y = y;
    this.z = z;
    this.world = utils.world(world);

    this.topic = topic;
    this.payload = payload;

    MQTTSender.count++;

    this.activate();
}

MQTTSender.count = 0;
MQTTSender.nodes = [];

MQTTSender.prototype.create = function (sign, isWallSign) {

    if (!isWallSign) {
        MQTTSender.nodes[MQTTSender.count] = new MQTTSender(sign.getX(), sign.getY() - 1, sign.getZ(), sign.getWorld(), getTopic(sign));
    } else {
        //TO-DO: implement wall sign
    }
};

MQTTSender.prototype.activate = function () {
    var drone = new Drone(this.x, this.y, this.z, 0, this.world);
    drone.place('137', false); //137 - COMMAND_BLOCK

    //console.log(this.world.getBlockAt(this.x, this.y, this.z).state/*.setCommand("say Ahoj!")*/);
    //this.world.getBlockAt(this.x, this.y, this.z).state.setCommand?('Say Ahoj!');

};

//============================== MQTT SENDER ==============================

command('pub', function (parameters, player) {
    var module = parameters[0];
    var channel = parameters[1];
    var message = parameters[2];

    var topic = module + '/' + channel; //+++++

    echo(player, 'Topic: ' + topic + '; Message: ' + message);
    MQTTReceiver.client.publish(topic, message);
});

command('cb', function (parameters, player) {
    var module = "Module";
    var channel = "Channel";
    var message = "Message";

    var topic = module + '/' + channel; //+++++

    //echo(player, 'Topic: ' + topic + '; Message: ' + message);
    //MQTTReceiver.client.publish(topic, message);
});


//========================== DRONE =============================


//========================== //DRONE =============================