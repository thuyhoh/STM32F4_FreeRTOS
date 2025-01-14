# RTOS
## I. Reference
- document : 
- video    : [play list youtube](https://www.youtube.com/playlist?list=PL831drV1RoWvU3AIoOKzeoz9AD625a97V) 
- IDE      : [STM32CubeIDE]() | [Keilcv5]() & [STM32CubeMx]() 
- RTOS     : [FreeRTOS]()
- Board    : STM32F407 Discovery | NUCLEO-F446RE

## II. Creating FreeRTOS base project for STM32 MCUs

- add FreeRTOS folder into project
\- in portable folder delete all folders exept GCC and MemMang
- add Config folder into project
![image](./img/Project.png)
- add Include part 
\- open Properties(alt+enter) => C/C++ General => Paths and Symbols => add include parth
![image](./img/Properties.png)
- wite "#define configSUPPORT_DYNAMIC_ALLOCATION 1" in main file
\
`` note fix error `` [video](https://www.youtube.com/watch?v=Ksjdh0KAEi0&list=PLxGj5QMILu9GIB2PIgY_8RoRpRPOLvQ3J&index=5)

## III. Introduction about RTOS 
### 1. Real Time Applications (RTAs)
- RTAs không phải là ứng dụng thực thi nhanh
- RTAs là một ứng dụng xác định thời gian. Có nghĩa là thời gian đáp ứng của các sự kiện là không đổi(độ lệch trong RTAs rát nhỏ tính bằng ms hoặc s trong Soft real time)
- đối với các ứng dụng Hard real time phải hoàn thành trong một khoảng thời gian giới hạn. nếu không thực hiện được sẽ dẫn đến lỗi hệ thống
### 2. Real Time OS
- Đây là một hệ điều hành được thiết kế đặc biệt để chạy các ứng dụng với thời gian rất chính xác và mức độ tin cậy cao.
- Để được coi là "thời gian thực", một hệ điều hành phải có thời gian tối đa đã biết cho mỗi hoạt động quan trọng mà nó thực hiện. Một số hoạt động này bao gồm
\- Xử lý các ngắt và ngoại lệ hệ thống nội bộ \
\- Xử lý các phần quan trọng \
\- Cơ chế lập lịch, v.v. 

### 3. RTOS vs GPOS 
![image](./img/RTOS_GPOS.png) 
#### Task Scheduling 
- GPOS
\- Việc lập lịch tác vụ không phải lúc nào cũng dựa trên "mức độ ưu tiên"
\- GPOS được lập trình để xử lý việc lập lịch theo cách mà nó có thể đạt được thông lượng(Throughput) cao. \
\- Trong GPOS, trình lập lịch thường sử dụng chính sách công bằng để phân phối luồng và quy trình vào CPU. \
\- Chính sách như vậy cho phép thông lượng tổng thể cao theo yêu cầu của các ứng dụng máy tính để bàn và máy chủ, nhưng không đảm bảo rằng các luồng hoặc quy trình có mức độ ưu tiên cao, quan trọng về thời gian sẽ thực thi thay vì các luồng có mức độ ưu tiên thấp hơn. 
- RTOS
\- Hầu hết sử dụng phương pháp lập lịch tác vụ ưu tiên dựa trên mức độ ưu tiên \
\- Mặt khác trong RTOS, các luồng thực thi theo thứ tự ưu tiên của chúng. Nếu một luồng có mức độ ưu tiên cao sẵn sàng chạy, nó sẽ tiếp quản CPU từ bất kỳ luồng có mức độ ưu tiên thấp nào có thể đang thực thi.  \
\- Tại đây, một luồng có mức độ ưu tiên cao sẽ được thực thi trên các luồng có mức độ ưu  lên thấp. Tất cả "thực thi luồng có mức độ ưu tiên thấp" sẽ bị tạm dừng. Thực thi luồng có mức độ ưu tiên cao sẽ
chỉ được ghi đè nếu một yêu cầu đến từ một luồng có mức độ ưu tiên cao hơn.
- ``note``
\- Thông lượng có nghĩa là  tổng số quy trình(Process) hoàn tất việc thực thi của chúng trên một đơn vị thời gian
- `` summary`` 
\- Đối với RTOS, việc đạt được khả năng dự đoán hoặc bản chất xác định thời gian quan trọng hơn so với thông lượng 
\- đối với GPOS, việc đạt được thông lượng cao hơn để thuận tiện cho người dùng quan trọng hơn 

#### Task Switching Latency
- Trong Máy tính, Độ trễ(Latency) có nghĩa là Thời gian trôi qua giữa một kích thích và phản ứng với nó.
- Độ trễ chuyển đổi tác vụ(Task Switching Latency) có nghĩa là khoảng thời gian giữa Sự kích hoạt của một sự kiện và thời điểm mà tác vụ xử lý sự kiện đó được phép chạy trên CPU
![image](./img/taskSwitchinglatency.png) \
![image](./img/taskSwitchingTime.png)

#### Priority Inversion
- Hiệu ứng đảo ngược ưu tiên (Priority Inversion) có nghĩa là khi một task vụ đang trong quá trình sử dụng tài nguyên thì một task khác có mức ưu tiên cao hơn truy nhập. Task có mức độ ưu tiên cao hơn không thể thay thế cho task trước đó  
\- đối với GPOS: Hiệu ứng đảo ngược ưu tiên(Priority Inversion) không đáng kể
\- đối với RTOS: Hiệu ứng đảo ngược ưu tiên(Priority Inversion) phải được giải quyết

#### Kernel Preemption
- Quyền ưu tiên(Preemption)
\- Trong tính toán, quyền ưu tiên là hành động tạm thời xóa tác vụ khỏi trạng thái đang chạy mà không cần sự hợp tác của tác vụ đó
- Trong RTOS 
\- các luồng thực thi theo thứ tự ưu tiên của chúng. Nếu một luồng có mức độ ưu tiên cao sẵn sàng để chạy, trong một khoảng thời gian nhỏ và giới hạn, nó sẽ tiếp quản CPU từ bất kỳ luồng có mức độ ưu tiên thấp hơn nào có thể đang thực thi mà chúng ta gọi là quyền ưu tiên.
\- Tác vụ có mức độ ưu tiên thấp hơn sẽ được thực hiện để rời khỏi CPU, nếu tác vụ có mức độ ưu tiên cao hơn muốn thực thi
\- Các hoạt động của hạt nhân(Kernel) RTOS có thể được chiếm đoạt trước
- Đối với GPOS
\- hạt nhân GPOS không thể được chiếm đoạt trước 
### 4. Multi-tasking
![image](./img/multitasking.png)

## IV. FreeRTOS Task Creation and Task Schedule
### 1. API Task Creation
``` C
BaseType_t xTaskCreate( TaskFunction_t pxTaskCode,
                        const char * const pcName,
                        const short uxStackDepth,
                        void * const pvParameters,
                        UBaseType_t uxPriority,
                        TaskHandle_t * const pxCreatedTask );
/*
    @param[pxTaskCode]
    @param[pcName]
    @param[uxStackDepth]
    @param[pvParameters]
    @param[uxPriority]
    @param[pxCreatedTask]

    @retval
*/
```
![imgae](./img/happenCreatetask.png)

### 2. API Task Implementation Function
``` C
void vATaskFuntion()
```

### 3. API Task Schedule 

## V. 
