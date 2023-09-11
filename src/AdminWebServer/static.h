#include <Arduino.h>

const char css[] PROGMEM = R"rawliteral(
@charset "UTF-8";
* {
  margin: 0;
  padding: 0;
  font-family: "Source Sans 3", "Helvetica", "Roboto", "Arial", sans-serif;
  color: #D2E2FF;
  background: #415273;
  font-style: normal;
  font-weight: 400;
  font-size: 16px;
  box-sizing: border-box;
}

a {
  text-decoration: none;
}

ul details {
  list-style: none;
}

svg {
  background-color: transparent;
}

.msg-box {
  position: absolute;
  width: 100%%;
  max-width: 414px;
  top: 0;
  left: 50%%;
  padding: 16px 32px;
  transform: translate(-50%%, 0);
  z-index: 1000;
  background-color:#286b59";
}
.msg-box p {
  background-color: inherit;
  text-align: center;
}

.container {
  position: relative;
  display: flex;
  flex-direction: column;
  align-items: center;
  justify-content: space-between;
  max-width: 414px;
  height: 100vh;
  box-shadow: 5px 5px 9px #374662, -5px -5px 9px #4b5e84;
  overflow-x: hidden;
  margin: 0 auto;
  padding: 32px 32px 42px 32px;
}
.container__top {
  display: flex;
  gap: 40px;
  width: 100%%;
  align-items: flex-start;
  justify-content: space-between;
}

button, input {
  border: none;
}
button:focus, input:focus {
  outline: none;
}

.name {
  width: 100%%;
  box-shadow: inset 5px 5px 9px #374662, inset -5px -5px 9px #4b5e84;
  padding: 8px 16px;
  border-radius: 50px;
  text-align: center;
}

.menu__button:checked ~ .menu__wrap {
  top: 0;
}
.menu__button-close {
  align-self: flex-end;
}
.menu__wrap {
  position: absolute;
  display: flex;
  flex-direction: column;
  gap: 32px;
  align-items: center;
  top: -100%%;
  right: 0;
  background: #415273;
  z-index: 100;
  width: 100%%;
  height: 100%%;
  transition: top 0.5s;
  box-shadow: inset 5px 5px 9px #374662, inset -5px -5px 9px #4b5e84;
  border-radius: 24px;
  padding: 32px 32px 42px 32px;
}
.menu__list {
  display: flex;
  flex-direction: column;
  list-style: none;
  padding: 0 32px 16px;
}
.menu__item {
  background-color: inherit;
}
.menu__item_caption {
  font-size: 1.5rem;
  margin-bottom: 16px;
}
.menu__item-link {
  display: block;
  background-color: inherit;
  font-size: 1rem;
  padding: 8px;
}
.menu__item-link:hover {
  color: #e5ebfd;
}

.footer {
  display: flex;
  align-items: flex-end;
  justify-content: space-between;
  width: 100%%;
}
.footer__column {
  display: flex;
  flex-direction: column;
  gap: 28px;
}

.button {
  font-size: 1rem;
  font-weight: 600;
  display: flex;
  justify-content: center;
  align-items: center;
  width: 64px;
  height: 64px;
  background: #415273;
  color: #D2E2FF;
  box-shadow: 5px 5px 9px #374662, -5px -5px 9px #4b5e84;
  text-shadow: 0 -1px 0 rgb(55, 70, 98), 0 1px 0 #4B5E84;
  user-select: none;
  border-radius: 20px;
  transition: box-shadow, color 0.3s ease-out;
}
.button svg {
  fill: #D2E2FF;
}
.button__icon {
  height: 54px;
  width: 54px;
}
.button_menu p {
  font-size: 32px;
  transform: rotate(90deg);
  padding-bottom: 4px;
}
.button_power {
  width: 96px;
  height: 96px;
  margin-bottom: 8px;
  font-size: 32px;
}
.button_power:before {
  transition: all 0.2s;
  content: "OFF";
}
.button__checkbox {
  display: none;
}
.button__checkbox:checked ~ .button {
  box-shadow: inset 5px 5px 9px #374662, inset -5px -5px 9px #4b5e84;
  background: none;
}
.button__checkbox:checked ~ .button_power:before {
  content: "ON";
  color: #b42828;
}
.button:hover {
  background: linear-gradient(145deg, #3b4a68, #46587b);
  color: #e5ebfd;
}
.button:active {
  box-shadow: inset 5px 5px 9px #374662, inset -5px -5px 9px #4b5e84;
  background: none;
}

.display {
  position: relative;
  display: flex;
  justify-content: center;
  align-items: center;
  height: 174px;
  min-height: 148px;
  box-shadow: inset 5px 5px 9px #374662, inset -5px -5px 9px #4b5e84;
  border-radius: 20px;
  width: 100%%;
  max-width: 286px;
  margin: 40px auto 28px auto;
}
.display__temp-wrap {
  position: relative;
  display: flex;
  background-color: transparent;
}
.display__temp-wrap:after {
  position: absolute;
  right: -24px;
  top: -16px;
  font-size: 32px;
  font-weight: 600;
  content: "℃";
  width: 32px;
}
.display__temp {
  display: block;
  font-size: 96px;
  width: 100px;
  height: 100px;
  font-weight: 600;
  text-align: center;
  color: #D2E2FF;
  background-color: transparent;
}
.display__icon {
  display: none;
  position: absolute;
  width: 44px;
  height: 48px;
}
.display__icon_fan {
  width: 52px;
}
.display__icon_left_top {
  top: 12px;
  left: 12px;
}
.display__icon_left_bottom {
  bottom: 12px;
  left: 12px;
}
.display__icon_right_top {
  top: 12px;
  right: 8px;
}
.display__icon_right_bottom {
  bottom: 12px;
  right: 8px;
}

.adjustment {
  position: relative;
  width: 64px;
  height: 148px;
  display: flex;
  flex-direction: column;
}
.adjustment__button {
  height: 100%%;
  width: 100%%;
  box-shadow: 5px 5px 9px #374662, -5px -5px 9px #4b5e84;
  border-radius: 0 0 20px 20px;
}
.adjustment__button:first-child {
  border-radius: 20px 20px 0 0;
  transform: translateY(3px);
}
.adjustment__button:first-child:after {
  position: absolute;
  box-shadow: 5px 5px 9px #374662, -5px -5px 9px #4b5e84;
  bottom: -3px;
  left: 0;
  content: "";
  width: 100%%;
  height: 6px;
}
.adjustment__button-text {
  transform: rotate(-90deg);
  background-color: transparent;
  font-size: 48px;
  font-weight: 600;
  text-shadow: 0 -1px 0 rgb(55, 70, 98), 0 1px 0 #4B5E84;
}

.selected {
  animation: flicker 1s infinite;
}

.settings {
  position: relative;
  display: flex;
  flex-direction: column;
  align-items: center;
  max-width: 414px;
  width: 100%%;
  height: 100vh;
  margin: 0 auto;
  padding: 32px;
}
.settings__button-close {
  position: absolute;
  top: 24px;
  right: 24px;
  height: 48px;
  width: 48px;
}
.settings__button-close svg {
  height: 32px;
  width: 32px;
}
.settings__title {
  font-size: 1.25rem;
  align-self: start;
  margin-left: 32px;
}
.settings__wrap {
  display: flex;
  flex-direction: column;
  align-items: center;
  gap: 4px;
  max-width: 414px;
  width: 100%%;
}
.settings__label {
  align-self: flex-start;
  margin-top: 12px;
  margin-left: 12px;
  font-size: 1rem;
}
.settings__select {
  background-image: url("data:image/svg+xml;base64,PHN2ZyB3aWR0aD0iMTYiIGhlaWdodD0iMTYiIHZpZXdCb3g9IjAgMCAxNiAxNiIgZmlsbD0ibm9uZSIgeG1sbnM9Imh0dHA6Ly93d3cudzMub3JnLzIwMDAvc3ZnIj4KPHBhdGggZD0iTTMuNSA1TDggMTBMMTIuNSA1SDMuNVoiIGZpbGw9IiNEMkUyRkYiLz4KPC9zdmc+Cg==");
  background-position: calc(100%% - 8px) center;
  background-repeat: no-repeat;
  -webkit-appearance: none;
  -moz-appearance: none;
  appearance: none;
  border: none;
}
.settings__select::-ms-expand {
  display: none;
}
.settings__select:focus {
  outline: none;
}
.settings__select option {
  font-weight: normal;
}
.settings__text-input {
  width: 100%%;
  box-shadow: inset 5px 5px 9px #374662, inset -5px -5px 9px #4b5e84;
  padding: 8px 16px;
  border-radius: 20px;
  font-size: 1rem;
}
.settings__button-wrap {
  width: 100%%;
  display: flex;
  flex-direction: column;
  justify-content: center;
  margin-top: 8px;
}
.settings__button {
  height: auto !important;
  width: 100%% !important;
  padding: 8px 16px;
  margin-top: 16px;
  font-size: 1.2rem !important;
  font-weight: normal;
}

@keyframes flicker {
  0%% {
    opacity: 1;
  }
  50%% {
    opacity: 0.3;
  }
  100%% {
    opacity: 1;
  }
}
@media (min-width: 600px) {
  .control {
    display: flex;
    justify-content: flex-end;
    width: 100%%;
    padding-top: 32px;
    padding-right: 128px;
  }
  .container {
    height: fit-content;
    width: 300px;
    border-radius: 40px;
    margin: 0;
    padding: 24px 24px 32px 24px;
  }
  .container__top {
    gap: 24px;
    width: 100%%;
  }
  .name {
    font-size: 0.75rem;
    width: 100%%;
    box-shadow: inset 5px 5px 9px #374662, inset -5px -5px 9px #4b5e84;
    padding: 8px;
    border-radius: 28px;
  }
  .menu__button-close {
    transform: scale(0.6);
  }
  .menu_caption {
    font-size: 1rem;
    margin-bottom: 16px;
  }
  .menu-link {
    font-size: 0.75rem;
  }
  .footer {
    display: flex;
    align-items: flex-end;
    justify-content: space-around;
    width: 100%%;
  }
  .footer__column {
    display: flex;
    flex-direction: column;
    gap: 24px;
  }
  .button {
    font-size: 0.75rem;
    height: 52px;
    width: 52px;
    border-radius: 12px;
  }
  .button__icon {
    transform: scale(0.6);
  }
  .button_menu p {
    font-size: 20px;
    padding-bottom: 2px;
  }
  .button_power {
    width: 64px;
    height: 64px;
    margin-bottom: 4px;
    font-size: 16px;
  }
  .display {
    height: 148px;
    max-width: 220px;
    margin: 32px auto 16px auto;
  }
  .display__temp-wrap {
    display: flex;
    background-color: transparent;
  }
  .display__temp-wrap:after {
    font-size: 20px;
    font-weight: 600;
    content: "℃";
    width: 24px;
  }
  .display__temp {
    font-size: 80px;
    width: 80px;
    height: 64px;
  }
  .display__icon {
    transform: scale(0.8);
  }
  .display__icon_left_top {
    top: 4px;
    left: 6px;
  }
  .display__icon_left_bottom {
    bottom: 4px;
    left: 6px;
  }
  .display__icon_right_top {
    top: 4px;
    right: 6px;
  }
  .display__icon_right_bottom {
    bottom: 4px;
    right: 6px;
  }
  .adjustment {
    width: 52px;
    height: 128px;
  }
  .adjustment__button {
    height: 100%%;
    width: 100%%;
    border-radius: 0 0 16px 16px;
  }
  .adjustment__button:first-child {
    border-radius: 16px 16px 0 0;
    transform: translateY(3px);
  }
  .adjustment__button:first-child:after {
    position: absolute;
    box-shadow: 5px 5px 9px #374662, -5px -5px 9px #4b5e84;
    bottom: -3px;
    left: 0;
    content: "";
    width: 100%%;
    height: 6px;
  }
  .adjustment__button-text {
    transform: rotate(-90deg);
    background-color: transparent;
    font-size: 28px;
    font-weight: 600;
    text-shadow: 0 -1px 0 rgb(55, 70, 98), 0 1px 0 #4B5E84;
  }
}
)rawliteral";
const char main_script[] PROGMEM = R"rawliteral(
    class Control {
    constructor(statusName, buttonElem, displayElem, controlStates, controlList) {
        this.statusName = statusName
        this.currentState = null;
        this.controlStates = controlStates;
        this.controlList = controlList;
        this.button = buttonElem;
        this.displayElem = displayElem;
        this.isSelected = false;
        this.newStatusListeners = [];
        this.button.addEventListener('change', this._changeListener.bind(this));
    }

    get type() {
        if (this.displayElem.tagName.toLowerCase() === 'input') {
            return 'input';
        } else {
            return 'icon';
        }

    }

    set buttonChangeEventListener(listener) {
        this.button.onchange = listener;
    }

    set state(state) {
        if (this.currentState) {
            this.displayElem.classList.remove(this.currentState.value);
        }
        this.currentState = state;
        this.displayElem.classList.add(state.value);
    }

    get value() {
        if (this.type === 'input') {
            return this.displayElem.value;
        } else {
            if (!this.currentState)
                return '';
            return this.currentState.key;
        }
    }

    set selected(val) {
        if (!val && this.isSelected) {
            this._newStatus();
            api.sendToServer();
        }

        this.isSelected = val;
        this.button.checked = val;
        if (val) {
            this.displayElem.classList.add('selected');
        } else {
            this.displayElem.classList.remove('selected');
        }
    }

    set onNewStatus(listener) {
        this.newStatusListeners.push(listener);
    }

    _newStatus() {
        this.newStatusListeners.forEach((listener) => {
            listener();
        });
    }

    _changeListener(e) {
        if (e.target.checked) {
            this.controlList.forEach((elem) => {
                if (elem.button.id !== this.button.id) {
                    elem.selected = false;
                }
            });
            this.selected = true;
        } else {
            this.selected = false;
        }
    }
}

class ControlsHandler {
    constructor(unselectTime) {
        this.unselectTime = unselectTime;
        let createTimer = function () {
            let elem = null;
            let timer = null;
            return function(e){
                if (e.target.name) {
                    elem = this.getControlByName(e.target.name);
                }
                if (timer) {
                    clearTimeout(timer);
                    timer = null;
                }
                timer = setTimeout(() => {
                    if (elem) elem.selected = false;
                }, this.unselectTime);
            }
        };
        this.unselectTimer = createTimer();
        this.controlList = [];
        this.powerButton = document.querySelector("#power-btn-id");
        this.buttonUp = document.querySelector('#button-up-id');
        this.buttonDown = document.querySelector('#button-down-id');
        this.buttonUp.addEventListener('click', this._buttonUpDownListener.bind(this));
        this.buttonUp.addEventListener('click', this.unselectTimer.bind(this));
        this.buttonDown.addEventListener('click', this._buttonUpDownListener.bind(this));
        this.buttonDown.addEventListener('click', this.unselectTimer.bind(this));
        this.newStatusListenerss = [];
        this.powerButton.onclick = () => {
            api.sendToServer();
        };

    }

    set status(status) {
        this.powerButton.checked = (String.fromCharCode(status.status.power) === 'o');

        this.controlList.forEach((control) => {
            const val = String.fromCharCode(status.status[control.statusName]);
            if (control.type === 'input') {
                control.displayElem.value = status.status[control.statusName];
            } else {
                control.controlStates.forEach((state) => {
                    if (state.key === val) {
                        control.state = state;
                    }
                });
            }
        });
    }

    get status() {
        let status = {
            'status': {
                'power': this.powerButton.checked ? 'o'.charCodeAt(0) : 'n'.charCodeAt(0)
            }
        }
        this.controlList.forEach((control) => {
            if (control.type === 'input') {
                status.status[control.statusName] = control.value;
            } else {
                status.status[control.statusName] = control.value.charCodeAt(0);
            }
        });
        return status;
    }

    getControlByName(name) {
        let ret = null;
        for (const control of this.controlList) {
            if (control.statusName === name) {
                ret = control;
                break;
            }
        }
        return ret;
    }


    set onNewStatus(listener) {
        this.newStatusListenerss.push(listener);
    }

    _newStatus() {
        this.newStatusListenerss.forEach((listener) => {
            listener(this.status);
        });
    }

    _buttonUpDownListener(e) {
        for (let elem of this.controlList) {
            if (elem.isSelected) {
                if (!elem.value) {
                    elem.state = elem.controlStates[0];
                    return;
                }
                if (elem.type === 'input') {
                    if (e.target === this.buttonUp || e.target.parentElement === this.buttonUp) {
                        elem.displayElem.value++;
                    } else {
                        elem.displayElem.value--;
                    }
                    return;
                }
                for (let i = 0; i < elem.controlStates.length; i++) {
                    if (elem.controlStates[i].key === elem.currentState.key) {
                        if (e.target === this.buttonUp || e.target.parentElement === this.buttonUp) {
                            if (i === elem.controlStates.length - 1) {
                                elem.state = elem.controlStates[0];
                            } else {
                                elem.state = elem.controlStates[i + 1];
                            }

                        } else {
                            if (i === 0) {
                                elem.state = elem.controlStates[elem.controlStates.length - 1];
                            } else {
                                elem.state = elem.controlStates[i - 1];
                            }
                        }
                        return;
                    }
                }
                return;
            }
        }
    }

    addControl(statusName, buttonId, displayId, controlStates, controlStateDefault) {
        const control = new Control(
            statusName,
            document.querySelector(`#${buttonId}`),
            document.querySelector(`#${displayId}`),
            controlStates,
            this.controlList
        );

        control.buttonChangeEventListener = this.unselectTimer.bind(this);
        control.onNewStatus = this._newStatus.bind(this);
        this.controlList.push(control);

        return this;
    }
}

class API {
    constructor(ip, version, first, second, msgBox) {
        this.ip = ip;
        this.version = version;
        this.first = first;
        this.second = second;
        this.msgBox = msgBox;
        this.socket = null;

    }

    connect() {
        if (this.socket) {
            this.socket.close()
            this.socket = null;
        }
        this.socket = new WebSocket(`ws://${this.ip}/${this.version}/${this.first}/${this.second}`);
        this.socket.onopen = this._onopen.bind(this);
        this.socket.onmessage = this._onmessage.bind(this);
        this.socket.onclose = this._onclose.bind(this);
        this.socket.onerror = this._onerror.bind(this);
        this.msgBox.sendInfo('Подключение к серверу...');
    }

    sendToServer() {
        let msg = {};
        switch (this.second) {
            case 'wifi':
                msg = {
                    'wifi': {
                        'mode': document.querySelector("#mode_id").value,
                        'ap_ssid': document.querySelector("#ssid_id").value,
                        'ap_pass': document.querySelector("#pass_id").value,
                        'conn_ssid': document.querySelector("#conn_ssid_id").value,
                        'conn_pass': document.querySelector("#conn_pass_id").value
                    }
                }
                break;
            case 'mqtt':
                msg = {
                    'mqtt': {
                        'user_key': document.querySelector("#user_key_id").value,
                        'dev_key': document.querySelector("#dev_id").value,
                        'user_password': document.querySelector("#pass_id").value,
                    }
                }
                break;
            case 'status':
                console.log(`controlsHandler.status = ${controlsHandler.status}`);
                msg = controlsHandler.status;
                break;

        }
        console.log(`sendToServer::msg = ${msg}`);
        this.socket.send(JSON.stringify(msg));
    }

    restartServer() {
        const settings = {
            'cmd': 'r'
        }
        this.socket.send(JSON.stringify(settings));
    }

    _onopen(e) {
        this.msgBox.sendInfo(`Подключение к ${this.ip} прошло успешно!!!`).timeout(5000);
    }

    _onclose(event) {
        if (event.wasClean) {
            console.log(`[close] Connection closed cleanly, code=${event.code} reason=${event.reason}`);
        } else {
            this.msgBox.sendError('Разрыв соединения!!! попробуйте обновить страницу!');
            console.log('[close] Connection died');
            this.connect();
        }
    }

    _onmessage(event) {
        console.log(`[message] Data received from server: ${event.data}`);
        const msg = JSON.parse(event.data);

        if (msg.hasOwnProperty('status')) {
            controlsHandler.status = msg;
        }
        if (msg.hasOwnProperty('mqtt')) {
            document.querySelector("#user_key_id").value = msg.mqtt.user_key;
            document.querySelector("#dev_id").value = msg.mqtt.dev_key;
            document.querySelector("#pass_id").value = msg.mqtt.user_password;
        }
        if (msg.hasOwnProperty('wifi')) {
            document.querySelector("#mode_id").value = msg.wifi.mode;
            document.querySelector("#ssid_id").value = msg.wifi.ap_ssid;
            document.querySelector("#pass_id").value = msg.wifi.ap_pass;
            document.querySelector("#conn_ssid_id").value = msg.wifi.conn_ssid;
            document.querySelector("#conn_pass_id").value = msg.wifi.conn_pass;
        }
        if (msg.hasOwnProperty('message')) {
            console.log(`msg.answer.error: ${msg.message.error}`);
            switch (msg.message.type) {
                case 'i':
                    this.msgBox.sendInfo(msg.message.text).timeout(3000);
                    break;
                case 'e':
                    this.msgBox.sendError(msg.message.text).timeout(3000);
                    break;
            }
        }
    }

    _onerror(error) {
        this.msgBox.sendError("ERROR!!!\n" + error).timeout(6000);
        console.log("ERROR!!!\n" + error);
    }
}

class MessageBox {
    constructor() {
        this.msgText = document.querySelector("#msg-box-text_id");
        this.msgWrap = document.querySelector("#msg-box_id");
    }

    close() {
        this.msgText.innerHTML = '';
        this.msgText.hidden = true;
        this.msgWrap.hidden = true;
    }

    _send(text) {
        this.msgText.innerHTML = text;
        this.msgText.hidden = false;
        this.msgWrap.hidden = false;
    }

    sendError(text) {
        this.msgWrap.style.background = "#6b2831";
        this._send(text);
        return this;
    }

    sendInfo(text) {
        this.msgWrap.style.background = "#286b59";
        this._send(text);
        return this;
    }

    timeout(time) {
        setTimeout(() => {
            this.close();
        }, time);
    }

}
)rawliteral";
const char index_script[] PROGMEM = R"rawliteral(
        document.querySelector('#menu-btn-close-id').onclick = () => {
        document.querySelector('#menu-btn-id').checked = false;
    };
    const swingControlStates = [
        {key: 'l', value: 'swing-icon__speed-1'},
        {key: 'm', value: 'swing-icon__speed-2'},
        {key: 'h', value: 'swing-icon__speed-3'},
        {key: 'H', value: 'swing-icon__speed-4'},
        {key: 'a', value: 'swing-icon__speed-a'}
    ]
    const modeControlStates = [
        {key: 'a', value: 'mode-icon__auto'},
        {key: 'c', value: 'mode-icon__cool'},
        {key: 'f', value: 'mode-icon__fan'},
        {key: 'h', value: 'mode-icon__heat'},
        {key: 'd', value: 'mode-icon__dry'}
    ]
    const fanControlStates = [
        {key: 'q', value: 'fan-icon__speed-1'},
        {key: 'l', value: 'fan-icon__speed-2'},
        {key: 'm', value: 'fan-icon__speed-3'},
        {key: 'M', value: 'fan-icon__speed-4'}
    ]

    const controlsHandler = new ControlsHandler(3000);
    controlsHandler
        .addControl('temp', 'temp-btn-id', 'temp-display-id')
        .addControl('swing_v', 'swing-btn-id', 'swing-display-id', swingControlStates)
        .addControl('mode', 'mode-btn-id', 'mode-display-id', modeControlStates)
        .addControl('fan', 'fan-btn-id', 'fan-display-id', fanControlStates)
        .onNewStatus = (status) => {
        console.log(status);
    };
    const msgBox = new MessageBox();
    const api = new API(globalIP, 'v1', 'control', 'status', msgBox);
    api.connect();
)rawliteral";
const char wifi_script[] PROGMEM = R"rawliteral(
    const msgBox = new MessageBox();
    const api = new API(globalIP, 'v1', 'settings', 'wifi', msgBox);
    api.connect();
)rawliteral";
const char mqtt_script[] PROGMEM = R"rawliteral(
    const msgBox = new MessageBox();
    const api = new API(globalIP, 'v1', 'settings', 'mqtt', msgBox);
    api.connect();
)rawliteral";