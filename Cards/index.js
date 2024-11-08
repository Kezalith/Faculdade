const { app, BrowserWindow } = require('electron');
const { screen } = require('electron');

let mainWindow;

app.on('ready', () => {
    const { width, height } = screen.getPrimaryDisplay().workAreaSize;

    mainWindow = new BrowserWindow({
        width: 960,
        height: height,
        resizable: false,
        autoHideMenuBar: true,
        icon: __dirname + '/icone.ico',
        x: width / 2,
        y: 0,
        frame: true,
        webPreferences: { nodeIntegration: true, contextIsolation: false }
    });

    mainWindow.setFullScreenable(false);
    mainWindow.setMinimizable(false);
    mainWindow.loadURL('file:///C:/Faculdade/Bandeira.html');
    mainWindow.on('blur', () => { mainWindow.close(); });
    mainWindow.webContents.on('before-input-event', (event, input) => {
        if (input.key === 'Escape') mainWindow.close();
    });
});
