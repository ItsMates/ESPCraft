'use strict';

var mqtt = require('sc-mqtt');
var utils = require('utils');
var JavaString = java.lang.String;

//=============================== EVENT SETUP ==============================

function sign_activation(event) {

    try {
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

                var sign = event.getClickedBlock().state;

                //TODO: Chceck, if the sign is not activated yet
                var avalible = true;

                if (avalible) {

                    var signCords = [sign.getX(), sign.getY(), sign.getZ()];
                    var blockCords = [sign.getX(), sign.getY() - 1, sign.getZ()];
                    var world = sign.getWorld();
                    var topic = getTopic(sign, event.getPlayer());
                    var payload = getPayload(sign);

                    if (sign.getLine(0) === 'SEM' || sign.getLine(0) === 'RECEIVER') {
                        MQTTNode.prototype.createReceiver(blockCords, signCords, world, topic);
                        echo(event.getPlayer(), 'Receiver ACTIVATED!');
                    }
                    else if (sign.getLine(0) === 'TAM' || sign.getLine(0) === 'TRANSMITTER') {
                        MQTTNode.prototype.createSender(blockCords, signCords, world, topic, payload);
                        echo(event.getPlayer(), 'Transmitter ACTIVATED!');
                    }
                    else {
                        echo(event.getPlayer(), 'Need Help?'); // Write SEM/RECEIVER | TAM/TRANSMITTER
                    }

                }
                else {
                    echo(event.getPlayer(), 'Receiver is already active.');
                }

            }
        }
    }
    catch (err) {
        console.log('Invalid activation - ' + err);
    }
}


events.playerInteract(sign_activation);

//=============================== TOPIC DECODING ===============================

function getTopic(sign, player) {

    return assemble(player.getPlayerListName(), sign.getLine(1), sign.getLine(2));

    function assemble(name, module, pin) {
        var topic = 'nvias/MC/' + name + '/' + module + '/' + pin;
        console.log('Topic: ' + topic);
        return topic;
    }
}

function getPayload(sign) {

    return sign.getLine(3);
}


//=============================== //TOPIC DECODING ===============================


//=============================== MQTT Receiver ===============================

function MQTTNode(blockCords, signCords, world, topic, payload) { // constructor function

    this.x = blockCords[0];
    this.y = blockCords[1];
    this.z = blockCords[2];

    this.signX = signCords[0];
    this.signY = signCords[1];
    this.signZ = signCords[2];

    this.world = utils.world(world);

    this.topic = topic;
    this.payload = payload;

    //is receiver block
    if (!payload) {
        for (var i = 0; i < MQTTNode.subTopics.length; i++) {
            if (topic === MQTTNode.subTopics[i]) {
                return;
            }
        }
        console.log('Subscribing to: ' + topic);
        MQTTNode.client.subscribe(topic);
        MQTTNode.subTopics.push(topic);
    }

    //is sender block
    else {

        var drone = new Drone(this.x, this.y, this.z, 0, this.world);
        drone.run('setblock ' + this.x + ' ' + (this.y - 1) + ' ' + this.z + ' command_block{Command:"jsp pub ' + this.topic + ' ' + this.payload + '"}');

        ///setblock ~ ~ ~ repeating_command_block{Command:"Command",auto:1b}

        //var drone = new Drone(this.x, this.y - 1, this.z, 0, this.world);
        //drone.place('137:1'); //137 - COMMAND_BLOCK

        ////console.log(this.world.getBlockAt(this.x, this.y - 1, this.z).state/*.setCommand("say Ahoj!")*/);
        //var commandBlock = server.getWorld(this.world.getUID()).getBlockAt(this.x, this.y - 1, this.z).state;
        //commandBlock.setCommand('say Ahoj!');
        ////console.log(commandBlock);

        //var sign = server.getWorld(this.world.getUID()).getBlockAt(this.signX, this.signY, this.signZ).state;
        //sign.setLine(3, 'Nazdar!');
    }
}

// Static variable shared by all instances
//MQTTReceiver.count = 0;
MQTTNode.receiving = [];
MQTTNode.sending = [];

MQTTNode.subTopics = [];

MQTTNode.client = mqtt.client('tcp://broker.mqttdashboard.com:1883');
MQTTNode.client.connect();

MQTTNode.prototype.createReceiver = function (blockCords, signCords, world, topic) {
    MQTTNode.receiving.push(new MQTTNode(blockCords, signCords, world, topic, null));
    //MQTTReceiver.nodes[MQTTReceiver.count] = new MQTTReceiver(blockCords, signCords, world, topic);
};

MQTTNode.prototype.createSender = function (blockCords, signCords, world, topic, payload) {
    if (!payload) { 
        payload = '0';
    }
    MQTTNode.sending.push(new MQTTNode(blockCords, signCords, world, topic, payload));
    //MQTTReceiver.nodes[MQTTReceiver.count] = new MQTTReceiver(blockCords, signCords, world, topic);
};

MQTTNode.client.onMessageArrived(function (topic, msg) {

    var i;
    var message = new JavaString(msg.payload);

    console.log('# MQTT MSG: ' + topic + ':' + message + '#');

    var deadConnection = false;

    if (parseInt(message) === 0 || message === 'OFF') {
        deadConnection = true;
        for (i = 0; i < MQTTNode.receiving.length; i++) {
            if (topic === MQTTNode.receiving[i].topic) {
                if (MQTTNode.receiving[i].signExists()) {
                    MQTTNode.receiving[i].deactivate();
                    deadConnection = false;
                }
            }
        }
    }

    else if (parseInt(message) === 1 || message === 'ON') {
        deadConnection = true;
        for (i = 0; i < MQTTNode.receiving.length; i++) {
            if (topic === MQTTNode.receiving[i].topic) {
                if (MQTTNode.receiving[i].signExists()) {
                    MQTTNode.receiving[i].activate();
                    deadConnection = false;
                }
            }
        }
    }

    //if (deadConnection) {
    //    console.log('Unsubscribing from: ' + topic);
    //    MQTTReceiver.client.unsubscribe(topic);         
    //    //TO-DO: Odstranit topic z MQTTReceiver.subTopics
    //}

});

MQTTNode.prototype.activate = function () {
    var drone = new Drone(this.x, this.y, this.z, 0, this.world);
    drone.place('152'); //152 - REDSTONE_BLOCK
};

MQTTNode.prototype.deactivate = function () {
    var drone = new Drone(this.x, this.y, this.z, 0, this.world);
    drone.place('42'); //42 - IRON_BLOCK
};

MQTTNode.prototype.signExists = function () {
    var block = this.world.getBlockAt(this.signX, this.signY, this.signZ);
    if (block.getType().toString() === 'SIGN') {
        return true;
    } else {
        return false;
    }
};

//// the following callbacks are optional 
//MQTTNode.client.onDeliveryComplete(function (deliveryToken) {
//    // optional callback to handle completion of outgoing messages
//});

MQTTNode.client.onConnectionLost(function (cause) {
    // optional callback to handle connection loss
    console.log('MQTT connection lost. Restarting the plugin...');
    refresh(true);
});

command('pub', function (parameters, player) {

    //if (MQTTNode.signExists()) {

        var topic = parameters[0];
        var payload = parameters[1];

        console.log('SENDING: Topic: ' + topic + '; Msg: ' + payload);
        MQTTNode.client.publish(topic, payload);
    //}
    //else {
    //    var drone = new Drone(this.x, this.y-1, this.z, 0, this.world);
    //    drone.place('1');
    //}
});



