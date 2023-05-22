#include <iostream>
#include <vector>
#include <string>
#include <unistd.h>
#include <sys/wait.h>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

class Pipe {
public:
    Pipe(const std::vector<std::string>& cmds) : m_pipes(cmds.size()), m_pids(cmds.size()) {
        for (int i = 0; i < cmds.size(); i++) {
            if (i > 0) {//非第一个进程，需要从前一个进程中读取数据
                pipe(m_pipes[i - 1]);
            }
            if (i < cmds.size() - 1) {//非最后一个进程，需要向后一个进程写入数据
                pipe(m_pipes[i]);
            }
            m_pids[i] = fork();//创建子进程
            if (m_pids[i] == 0) {//子进程逻辑
                if (i > 0) {//非第一个进程，从前一个进程中读取数据
                    dup2(m_pipes[i - 1][0], STDIN_FILENO);
                    close(m_pipes[i - 1][1]);
                }
                if (i < cmds.size() - 1) {//非最后一个进程，向后一个进程写入数据
                    dup2(m_pipes[i][1], STDOUT_FILENO);
                    close(m_pipes[i][0]);
                }
                std::vector<char*> args;
                for (int j = i + 1; j < cmds.size(); j++) {
                    args.push_back(const_cast<char*>(cmds[j].c_str()));
                }
                args.push_back(NULL);
                execvp(cmds[i].c_str(), &args[0]);
            } else {//父进程逻辑
                if (i > 0) {//关闭管道中的读端
                    close(m_pipes[i - 1][0]);
                }
                if (i < cmds.size() - 1) {//关闭管道中的写端
                    close(m_pipes[i][1]);
                }
            }
        }
    }
    ~Pipe() {
        for (int i = 0; i < m_pids.size(); i++) {
            waitpid(m_pids[i], NULL, 0);//等待每个子进程结束
        }
    }
    int read(int index, char* buf, int size) {//从 index 进程中读取数据，存储到 buf 中，最多读取 size 个字节，返回实际读取的字节数
        return ::read(m_pipes[index][0], buf, size);
    }
    int write(int index, const char* buf, int size) {//向 index 进程中写入数据，最多写入 size 个字节，返回实际写入的字节数
        return ::write(m_pipes[index][1], buf, size);
    }
private:
    std::vector<int[2]> m_pipes;//用来存储每个管道的文件描述符
    std::vector<pid_t> m_pids;//用来存储每个子进程的 pid
};

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " input_file output_file" << std::endl;
        return 1;
    }
    std::vector<std::string> cmds = {"./input_filter", "./transform_filter", "./output_filter"};
    Pipe pipe(cmds);
    std::ofstream outfile(argv[2]);
    char buf[1024];
    int n;
    while ((n = pipe.read(2, buf, sizeof(buf))) > 0) {//从输出程序的管道中读取数据
        outfile.write(buf, n);//将数据写入输出文件中
    }
    return 0;
}