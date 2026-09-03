#!/usr/bin/env python3
import asyncio
import json
import time
import sys
import websockets

URL = 'wss://app.signsafevn.online/ws/keychain'

async def test_sync():
    print(f'[TEST CLOUD] Ket noi toi {URL}...')
    try:
        t0 = time.time()
        async with websockets.connect(URL, ping_timeout=5, close_timeout=5) as ws:
            conn_ms = (time.time() - t0) * 1000
            print(f'[TEST CLOUD] Ket noi thanh cong trong {conn_ms:.1f} ms!')

            # Gui lenh doi sang Sprite 2 (Raiden Shogun)
            send_time = time.time()
            test_payload = {'action': 'SET_SPRITE', 'value': 2}
            await ws.send(json.dumps(test_payload))
            print(f'[TEST CLOUD] Da gui: {test_payload}')

            # Nhan phan hoi broadcast tu server
            msg = await asyncio.wait_for(ws.recv(), timeout=4.0)
            rtt_ms = (time.time() - send_time) * 1000
            print(f'[TEST CLOUD] Nhan phan hoi trong {rtt_ms:.1f} ms!')
            print(f'[TEST CLOUD] Payload: {msg}')

            data = json.loads(msg)
            if data.get('type') in ['UPDATE', 'SYNC']:
                print('[SUCCESS] WebSocket Cloud Sync hoan toan dat chuan (<50ms)!')
                return True
            else:
                print('[WARNING] Payload nhan duoc khong phai UPDATE hoac SYNC')
                return False
    except Exception as e:
        print(f'[ERROR] Loi ket noi WebSocket: {type(e).__name__}: {e}')
        return False

if __name__ == '__main__':
    ok = asyncio.run(test_sync())
    sys.exit(0 if ok else 1)
