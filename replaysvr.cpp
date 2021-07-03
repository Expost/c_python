#include <pybind11/pybind11.h>
#include <pybind11/embed.h>

namespace py = pybind11;
py::scoped_interpreter guard{};
py::module g_logic;

void replay_log(int log_level, char *str)
{
    printf("[%d] %s\n", log_level, str);
}

PYBIND11_MODULE(replaysvr, m)
{
    m.def("replay_log", &replay_log, "print log", py::arg("log_level"), py::arg("str"));
}

extern "C" int init()
{
    g_logic = py::module::import("logic");
    auto init_func = g_logic.attr("init");
    py::object result = init_func();
    int ret = result.cast<int>();
    printf("init result is %d\n", ret);
    return 0;
}

extern "C" int on_recv()
{
    auto on_recv_func = g_logic.attr("on_recv");
    py::object result = on_recv_func("01234567890");
    int ret = result.cast<int>();

    printf("on_recv result is %d\n", ret);

    // call except func
    auto except_func = g_logic.attr("exception");
    try
    {
        except_func();
    }
    catch(const std::exception& e)
    {
        printf("except...\n");
    }
    
    
    return 0;
}
