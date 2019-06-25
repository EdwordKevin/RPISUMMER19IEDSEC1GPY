const elec = require("electron");
const ipc = elec.ipcMain

let win;

//create window
function createWin (){
    //hide defaute menu
    elec.Menu.setApplicationMenu(null);

    win = new elec.BrowserWindow({
        width: 800,
        height: 600,
        webPreferences: {
          nodeIntegration: true
        },
        frame:false,
        resizable: false
    });

    //load html
    win.loadFile('index.html');

    //turn on developer tools
    win.webContents.openDevTools();

    //cancel referance
    win.on('closed', () => {
        win = null;
    });
}

//start after init
elec.app.on('ready', createWin);

//quit when window closed
elec.app.on('window-all-closed', () => {
    elec.app.quit();
})

ipc.on('window-close',()=>{
    win.close();
})

ipc.on("save",(sys,data)=>{
    console.log(data);
});