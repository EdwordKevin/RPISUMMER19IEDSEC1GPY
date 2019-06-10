bt_anim("closebt","img/close.png","img/closehvr.png");//add close button anime

//add close function
var ipc = require('electron').ipcRenderer;
$("#closebt").click(function (){
    ipc.send('window-close');
});