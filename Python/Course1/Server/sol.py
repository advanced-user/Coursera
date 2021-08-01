import asyncio


d = dict()


async def query_processing(reader, writer):
    data = await reader.read(1024)
    resp = await process_data(data.decode())

    writer.write(resp.encode())


async def process_data(data):
    result = 'error\nwrong command\n\n'
    data = data.strip().split(' ')

    if data[0] == 'put':
        result = await put(data)
    elif data[0] == 'get':
        result = await get(data)

    return result


async def get(data):
    result = "ok\n"

    if data[1] == '*':
        for key in d:
            for val_time in d[key]:
                result += key + ' ' + val_time[0] + ' ' + val_time[1] + '\n'
    else:
        if data[1] in d:
            for val_time in d[data[1]]:
                result += data[1] + ' ' + val_time[0] + ' ' + val_time[1] + '\n'

    result += '\n'

    return result


async def put(data):
    result = 'ok\n\n'

    try:
        if data[1] in d:
            d[data[1]].append(data[2], data[3])
        else:
            d[data[1]] = {(data[2], data[3])}
    except IndexError:
        result = 'error\nwrong command\n\n'

    return result


def run_server(host, port):
    loop = asyncio.get_event_loop()
    coro = asyncio.start_server(query_processing, host, port, loop=loop)

    server = loop.run_until_complete(coro)
    try:
        loop.run_forever()
    except KeyboardInterrupt:
        pass

    server.close()
    loop.run_until_complete(server.wait_closed())
    loop.close()


#run_server("127.0.0.1", 8888)

