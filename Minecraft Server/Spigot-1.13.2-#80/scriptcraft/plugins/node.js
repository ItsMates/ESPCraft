/*

function MQTTNode() { // constructor function
    var privateVariable = "foo";  // Private variable 

    this.publicVariable = "bar";  // Public variable 

    this.privilegedMethod = function () {  // Public Method
        alert(privateVariable);
    };
}

// Instance method will be available to all instances but only load once in memory 
MQTTNode.prototype.publicMethod = function () {
    alert(this.publicVariable);
};

// Static variable shared by all instances
MQTTNode.staticProperty = "baz";


*/

//===============================================================================================

//utils = require('utils');

//function FromMqttNode(x, y, z, world) { // constructor function

//    this._x = x; 
//    this._y = y; 
//    this._z = z;  
//    this._world = utils.world(world); 

//    this.onMessageArrivedHandler = function (topic, message) {  // Public Method
//        if (topic === 'TOUCH_MODULE/TOUCH' && message === '1') {
//            this._activate();
//        }
//        if (topic === 'TOUCH_MODULE/TOUCH' && message === '1') {
//            this._deactivate();
//        }
//    };

//    FromMqttNode.count++;
//}

//// Static variable shared by all instances
//FromMqttNode.count = 0;

//FromMqttNode.prototype._activate = function () {
//    var drone = new Drone(this._x, this._y, this._z, 0, utils.world('world'));
//    drone.place('152'); //152 - REDSTONE_BLOCK
//};

//FromMqttNode.prototype._deactivate = function () {
//    var drone = new Drone(this._x, this._y, this._z, 0, utils.world('world'));
//    drone.place('42'); //42 - IRON_BLOCK
//};





//===============================================================================================

//function ToMqttNode(x, y, z, world) { // constructor function

//    this._x = x;
//    this._y = y;
//    this._z = z;
//    this._world = world;

//    this.update = function () {  // Public Method
//        alert(privateVariable);
//    };
//}

//// Instance method will be available to all instances but only load once in memory 
//ToMqttNode.prototype.publicMethod = function () {
//    alert(this.publicVariable);
//};

//// Static variable shared by all instances
//ToMqttNode.staticProperty = "baz";