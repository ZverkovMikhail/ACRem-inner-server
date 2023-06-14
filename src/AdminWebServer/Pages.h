#include <Arduino.h>

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML>
<html lang="ru-RU">
<head>
    <meta charset="UTF-8"/>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <title>AC-Remote</title>
    <link rel="preconnect" href="https://fonts.googleapis.com">
    <link rel="preconnect" href="https://fonts.gstatic.com" crossorigin>
    <link href="https://fonts.googleapis.com/css2?family=Source+Sans+3:wght@400;600&display=swap" rel="stylesheet">
    <style>
        :root {
            --color-light: 89, 110, 148;
            --color-shadow: 43, 57, 81;
            --color-glow: 0, 92, 241;
            --color-typo-link: 0, 92, 241;
        }

        body {
            text-align: center;
            background: #415273;
            color: #D2E2FF;
            font-family: 'Source Sans 3', sans-serif;
            font-style: normal;
            font-weight: 400;
            font-size: 12px;
        }

        input {
            border: none;
        }

        .container {
            position: relative;
        }

        .msg-box {
            position: absolute;
            width: 100%%;
            max-width: 414px;
            top: 0;
            left: 50%%;
            transform: translate(-50%%, 0);
        }

        .msg-box p {
            margin: 16px;
        }

        .settings-wrap {
            display: flex;
            flex-direction: column;

        }

        .settings-wrap label {
            text-align: left;
            margin-top: 8px;
            margin-left: 8px;
            margin-bottom: 2px;
        }

        .button {
            color: #D2E2FF;
            font-family: 'Source Sans 3', sans-serif;
            background: #415273;
            border-radius: 20px;
            margin-top: 32px;
            padding: 8px;
            text-shadow: 0 -1px 0 rgba(var(--color-shadow), 0.08),
            0 1px 0 rgba(var(--color-light), 1);
            box-shadow: inset 1px 1px 1px rgba(var(--color-light), 1),
            -2px -2px 2px rgba(var(--color-light), 0.9),
            -4px -4px 6px rgba(var(--color-light), 0.9),
            inset -1px -1px 1px rgba(var(--color-shadow), 0.06),
            2px 2px 2px rgba(var(--color-shadow), 0.08),
            4px 4px 6px rgba(var(--color-shadow), 0.08);

            transition: color 0.3s,
            text-shadow 0.3s,
            box-shadow 0.6s;
        }

        .button:hover {
            color: var(--color-typo-link);
            text-shadow: 0 -1px 0 rgba(var(--color-shadow), 0.08),
            0 1px 0 rgba(var(--color-light), 1),
            0 0 1px rgba(var(--color-light), 0.7),
            0 0 4px rgba(var(--color-glow), 0.08),
            0 0 8px rgba(var(--color-glow), 0.08);
            box-shadow: inset 1px 1px 1px rgba(var(--color-light), 1),
            -3px -3px 3px rgba(var(--color-light), 1),
            -5px -5px 6px rgba(var(--color-light), 1),
            inset -1px -1px 1px rgba(var(--color-shadow), 0.06),
            3px 3px 3px rgba(var(--color-shadow), 0.085),
            5px 5px 6px rgba(var(--color-shadow), 0.085);
        }

        .button:active {
            box-shadow: 1px 1px 1px rgba(var(--color-light), 1),
            inset -2px -2px 2px rgba(var(--color-light), 0.9),
            inset -3px -3px 4px rgba(var(--color-light), 0.9),
            -1px -1px 1px rgba(var(--color-shadow), 0.06),
            inset 2px 2px 2px rgba(var(--color-shadow), 0.08),
            inset 3px 3px 4px rgba(var(--color-shadow), 0.08);
        }


        .text-input {
            text-align: center;
            background: #415273;
            box-shadow: 1px 1px 1px rgba(var(--color-light), 1),
            inset -2px -2px 2px rgba(var(--color-light), 0.9),
            inset -3px -3px 4px rgba(var(--color-light), 0.9),
            -1px -1px 1px rgba(var(--color-shadow), 0.06),
            inset 2px 2px 2px rgba(var(--color-shadow), 0.08),
            inset 3px 3px 4px rgba(var(--color-shadow), 0.08);
            border-radius: 24px;
            padding: 8px 24px;
        }

        .text-input:focus {
            outline: none;
        }

        .select {
            position: relative;
            box-sizing: border-box;
            border: 0;
            border-radius: 24px;
            background-image: url('https://s3-us-west-2.amazonaws.com/s.cdpn.io/1329536/icon_select_s.svg');
            background-position: calc(100% - 8px) center;
            background-repeat: no-repeat;

            -webkit-appearance: none;
            -moz-appearance: none;
            appearance: none;
        }

        .select::-ms-expand {
            display: none;
        }

        .select:focus {
            outline: none;
        }

        .select option {
            font-weight: normal;
        }
    </style>
</head>
<body>
<div class="container" id="container">
    <div id="msg-box_id" class="msg-box">
        <p id="msg-box-text_id"></p>
    </div>
    <div style="display:flex; flex-direction: column; align-items: center;" action='action' method='post'>
        <h2>Настройки</h2>
        <div class="settings-wrap">
            <label for="mode_id">Mode:</label>
            <select class="select text-input" id='mode_id'>
                <option value="2">Точка доступа</option>
                <option value="1">Подключение к роутеру</option>
            </select>
            <label for="ssid_id">Access point SSID:</label>
            <input class="text-input" type='text' id='ssid_id' value=''>
            <label for="pass_id">Access point Password:</label>
            <input class="text-input" type='text' id='pass_id' value=''>
            <label for="conn_ssid_id">Router SSID:</label>
            <input class="text-input" type='text' id='conn_ssid_id' value=''>
            <label for="conn_pass_id">Router Password:</label>
            <input class="text-input" type='text' id='conn_pass_id' value=''>
            <input class="button" type='button' onclick="sendToServer()" value='Изменить настройки'>
            <input class="button" type='button' onclick="restartServer()" value='Перезапустить сервер'>
        </div>

    </div>
</div>

</body>
<script>
    const ip = '%IP_ADDR%';
    let socket = new WebSocket(`ws://${ip}/wifi_settings`);

    socket.onopen = function (e) {
        msgBox(true, false, `Подключение к ${ip} прошло успешно!!!`);
        setTimeout(() => {
            msgBox(false, false, "");
        }, 5000);

    };

    socket.onmessage = function (event) {
        console.log(`[message] Data received from server: ${event.data}`);
        const msg = JSON.parse(event.data);
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
                    msgBox(true, false, msg.message.text);
                    break;
                case 'e':
                    msgBox(true, true, msg.message.text);
                    break;
            }
            setTimeout(() => {
                msgBox(false, false, "");
            }, 7000);
        }
    };

    socket.onclose = function (event) {
        if (event.wasClean) {
            console.log(`[close] Connection closed cleanly, code=${event.code} reason=${event.reason}`);
        } else {
            msgBox(true, true, "Разрыв соединения!!! попробуйте обновить страницу!");
            console.log('[close] Connection died');
            socket = new WebSocket(`ws://${ip}/wifi_settings`);
        }
    };

    socket.onerror = function (error) {
        msgBox(true, true, "ERROR!!!\n" + error);
    };

    function sendToServer() {
        const settings = {
            'wifi': {
                'mode': document.querySelector("#mode_id").value,
                'ap_ssid': document.querySelector("#ssid_id").value,
                'ap_pass': document.querySelector("#pass_id").value,
                'conn_ssid': document.querySelector("#conn_ssid_id").value,
                'conn_pass': document.querySelector("#conn_pass_id").value
            }
        }
        socket.send(JSON.stringify(settings));
    }

    function restartServer() {
        const settings = {
            'cmd': 'r'
        }
        socket.send(JSON.stringify(settings));
    }

    function msgBox(show = true, isError = false, text) {
        const msgText = document.querySelector("#msg-box-text_id");
        const msgWrap = document.querySelector("#msg-box_id");
        if (isError)
            msgWrap.style.background = "#6b2831";
        else
            msgWrap.style.background = "#286b59";

        msgText.innerHTML = text;
        msgText.hidden = !show;
        msgWrap.hidden = !show;
    }
</script>
</html>)rawliteral";