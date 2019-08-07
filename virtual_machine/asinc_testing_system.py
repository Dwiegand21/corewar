import itertools
import argparse
import asyncio
import os
sem = asyncio.BoundedSemaphore(30)
progress = 0


class ExistingDir(argparse.Action):
    def __call__(self, parser, namespace, values, option_string=None):
        prospective_dir = values
        if not os.path.isdir(prospective_dir):
            raise argparse.ArgumentError("dir:{0} is not a valid path".format(prospective_dir))
        if os.access(prospective_dir, os.R_OK):
            setattr(namespace, self.dest, prospective_dir)
        else:
            raise argparse.ArgumentError("dir:{0} is not a valid path".format(prospective_dir))

dump_file = open('dump_file.txt', 'w')
dump_file.close()


async def find_error(player1, player2, directory):
    global progress

    async def sparring(dump_cycle):
        async with sem:
            proc1 = await asyncio.create_subprocess_exec(
                            './origin_sources/champs/championships/2018/corewar',
                            '-d',
                            str(dump_cycle),
                            directory + '/' + player1,
                            directory + '/' + player2,
                            stdout=asyncio.subprocess.PIPE,
                            stderr=asyncio.subprocess.PIPE)
            stdout1, stderr1 = await proc1.communicate()
            proc2 = await asyncio.create_subprocess_exec(
                            './executable/corewar',
                            '-d',
                            str(dump_cycle),
                            directory + '/' + player1,
                            directory + '/' + player2,
                            stdout=asyncio.subprocess.PIPE,
                            stderr=asyncio.subprocess.PIPE)
            stdout2, stderr2 = await proc2.communicate()

            # progress += 1
            # print(progress)
            # print(b'stdout1 ' + stdout1, b'stderr1 ' + stderr1, b'stdout2 ' + stdout2, b'stderr2 ' + stderr2, sep='\n')
            return True if stdout1 == stdout2 else False
    dump_time = 0
    while dump_time <= 30000:
        result = await sparring(dump_time)
        # print(result)
        if result:
            # print(dump_time)
            print('\033[32m' + player1 + ' ' + player2 + ' ' + str(dump_time) + '\033[0m')
            dump_time += 5000
        else:
            # dump_step = 1000
            # step_side = -1
            # result = 0
            # while dump_step > 10:
            #     dump_time += dump_step * step_side
            #     if result != await sparring(dump_time):
            #         dump_step = dump_step / 2
            #         step_side *= -1
            #         result = 0 if result else 1
            print('\033[91m' + player1 + ' ' + player2 + ' ' + str(dump_time) + '\033[0m')
            with open('dump_file.txt', 'a') as f:
                f.write(player1 + ' ' + player2 + ' ' + str(dump_time) + '\n')
            break
    progress += 1
    # print(progress, end='\r')


def start_testing():
    parser = argparse.ArgumentParser()
    parser.add_argument('directory', action=ExistingDir, help='path to champs bins')
    args = parser.parse_args()
    champs_list = list(itertools.product(os.listdir(args.directory), repeat=2))
    loop = asyncio.get_event_loop()
    tasks = [loop.create_task(find_error(*i, args.directory)) for i in champs_list]
    loop.run_until_complete(asyncio.gather(*tasks))


if __name__ == '__main__':
    start_testing()
