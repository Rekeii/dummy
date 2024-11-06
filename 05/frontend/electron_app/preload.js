const { contextBridge } = require('electron');
const addon = require('./build/Release/addon');

contextBridge.exposeInMainWorld('api', {
    fetchInventory: () => addon.fetchInventory()
});
