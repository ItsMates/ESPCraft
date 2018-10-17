var mqtt = require('sc-mqtt'),
    foreach = require('utils').foreach,
    client = mqtt.client('tcp://127.0.0.1:1884', 'Minecraft'),
    //client = mqtt.client(),
    JavaString = java.lang.String;

client.connect();
client.subscribe('arduino');

client.onMessageArrived(function (topic, message) {
    echo('NEW MESSAGE!');
    var msgText = '' + new JavaString(message.payload);
    if (topic == 'arduino' && msgText.equals('BUTTON')) {
        /*
          change the time in each of the server's worlds.
          Day becomes night, night becomes day.
         */
        foreach(server.worlds, function (world) {
            echo('TIME CHANGE!');
            //client.publish('light','ON');

            var time = world.time + 12000; // adds 1/2 day to time
            world.time = time;
        });
    }
});

// the following callbacks are optional 
client.onDeliveryComplete(function (deliveryToken) {
    // optional callback to handle completion of outgoing messages
    // (message ACK'd by receiver)
});
client.onConnectionLost(function (cause) {
    // optional callback to handle connection loss
});

command('lighton', function (parameters, player) {
    echo(player, 'ON');
    client.publish('light', 'ON');
});

command('lightoff', function (parameters, player) {
    echo(player, 'OFF');
    client.publish('light', 'OFF');
});

command('policka', function (parameters, player) {
    echo(player, 'policka');
    client.publish('policka', '0');
});