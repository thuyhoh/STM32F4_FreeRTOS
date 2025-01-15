# RTOS
## I. Reference
- document : 
- video    : [play list youtube](https://www.youtube.com/playlist?list=PL831drV1RoWvU3AIoOKzeoz9AD625a97V) 
- Software 
\- IDE      : [STM32CubeIDE]() | [Keilcv5]() & [STM32CubeMx]()
\- other    : [SEGGER SystemView]()
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

## IV. FreeRTOS API Task Creation and Task Implement Function
### 1. API Task Creation
``` C
BaseType_t xTaskCreate( TaskFunction_t pxTaskCode,
                        const char * const pcName,
                        const short uxStackDepth,
                        void * const pvParameters,
                        UBaseType_t uxPriority,
                        TaskHandle_t * const pxCreatedTask );
/*
    @param[pxTaskCode]    : hàm xử lý của task 
    @param[pcName]        : tên của task
    @param[uxStackDepth]  : độ dài của stack cho task
    @param[pvParameters]  : tham số truyền vào cho hàm pxTaskCode
    @param[uxPriority]    : mức ưu tiên của task 
    @param[pxCreatedTask] : Task handle chúa thông tin của task được tạo

    @retval : trả về
    note : có thẻ sử dụng hàm để kiểm tra API có thành công hay không
*/
```
### 2. API Task Implementation Function
``` C
void vATaskFuntion(void *arg)
{
    // code
    while(1)
    {
        // code
    }
    // Khi thoát khỏi vòng lạp phải cần xóa trước khi thoát hàm
    vTaskDelete(NULL);    
}
```

### 3. Quá trình sau khi gọi API xTaskCreate
- các thông tin của Task mới sẽ được lưu trong Heap trên RAM
![imgae](./img/happenCreatetask.png)


## V. Idle Task 
![imgae](./img/Idle_Task.png)
- Idle Task được tự động tạo ra khi trình lập lịch RTOS được khởi động để đảm bảo luôn có ít nhất một nhiệm vụ có thể chạy.
- Task này được tạo ở mức ưu tiên thấp nhất có thể để đảm bảo không sử dụng bất kỳ thời gian CPU nào nếu có các nhiệm vụ ứng dụng có mức ưu tiên cao hơn ở trạng thái sẵn sàng.
- Idle Task có trách nhiệm giải phóng bộ nhớ được RTOS phân bổ cho các nhiệm vụ đã bị xóa
- Có thể cung cấp một hàm Hook ứng dụng trong tác vụ nhàn rỗi để gửi CPU đến chế độ năng lượng thấp khi không có tác vụ hữu ích nào đang thực thi.

## VI. FreeRTOS Timer Services Task (Timer_svc)
- Điều này cũng được gọi là tác vụ daemon hẹn giờ
- Tác vụ daemon hẹn giờ xử lý "Bộ hẹn giờ phần mềm"
- Tác vụ này được tạo tự động khi trình lập lịch được khởi động và nếu configUSE_TIMERS = 1 trong FreeRTOSConfig.h
- RTOS sử dụng daemon này để quản lý bộ hẹn giờ phần mềm FreeRTOS và không có thứ gì khác.
- Nếu bạn không sử dụng bộ hẹn giờ phần mềm trong ứng dụng FreeRTOS của mình thì bạn cần sử dụng tác vụ daemon hẹn giờ này. Đối với điều đó, chỉ cần đặt configUSE_TIMERS = 0 trong FreeRTOSConfig.h
- Tất cả các hàm gọi lại bộ hẹn giờ phần mềm thực thi trong ngữ cảnh của tác vụ daemon hẹn giờ

## VI. Task Scheduling and API xTaskStartScheduler()
### 1. Trình lập lịch (Scheduler)
- nó chỉ là một đoạn mã thực hiện việc chuyển đổi tác vụ vào và chuyển đổi tác vụ ra theo chính sách lập lịch đã chọn.
- Trình lập lịch là lý do tại sao nhiều tác vụ chạy trên hệ thống của bạn một cách hiệu quả
- Công việc cơ bản của trình lập lịch là xác định tác vụ tiềm năng tiếp theo sẽ chạy trên CPU
- Trình lập lịch có khả năng chiếm quyền trước một tác vụ đang chạy nếu bạn định cấu hình như vậy

### 2. Chính sách/kiểu lập lịch (Scheduling Policies)
- Lập lịch ưu tiên đơn giản (Round robin)
- Lập lịch ưu tiên dựa trên mức độ ưu tiên
- Lập lịch hợp tác
- ``note``
\- Chính sách lập lịch là thuật toán được trình lập lịch sử dụng để quyết định tác vụ nào sẽ thực hiện tại bất kỳ thời điểm nào.
\- FreeRTOS hoặc hầu hết các hệ điều hành thời gian thực có khả năng sẽ sử dụng Lập lịch ưu tiên dựa trên mức độ ưu tiên theo mặc định

### 3. FreeRTOS Scheduling 
- Scheduler là một phần của mã hạt nhân(Kernel) chịu trách nhiệm quyết định tác vụ nào sẽ được thực thi tại bất kỳ thời điểm cụ thể nào trên CPU.
- Chính sách lên lịch là thuật toán được trình lên lịch sử dụng để quyết định tác vụ nào sẽ thực thi tại bất kỳ thời điểm nào.
- configUSE_PREEMPTION của mục có thể cấu hình freeRTOSConfig.h quyết định chính sách lên lịch trong freeRTOS. \
\- Nếu configUSE_PREEMPTION = 1, thì chính sách lên lịch sẽ là lập lịch ưu tiên dựa trên mức độ ưu tiên. \
\- Nếu configUSE_PREEMPTION = 0, thì chính sách lên lịch sẽ là lập lịch hợp tác

### 4. FreeRTOS Scheduler Implementation
- Trong FreeRTOS, mã trình lập lịch thực sự là sự kết hợp của Mã chung FreeRTOS + Mã cụ thể của Kiến trúc \
![image](./img/scheduler.png) 
- Mã cụ thể về kiến ​​trúc chịu trách nhiệm đạt được lập lịch tác vụ.
- Tất cả các mã và cấu hình cụ thể về kiến ​​trúc đều được triển khai trong port.c và portmacro.h
Nếu bạn đang sử dụng bộ xử lý ARM Cortex Mx thì bạn sẽ có thể định vị các trình xử lý ngắt bên dưới trong port.c, đây là một phần của triển khai trình lập lịch của freeRTOS \
![image](./img/Portc.png)
- vPortSVCHandler()     : Được sử dụng để khởi chạy tác vụ đầu tiên. Được kích hoạt bởi lệnh SVC
- vPortSVCHandler()     : Được sử dụng để đạt được ngữ cảnh chuyển đổi giữa các tác vụ Được kích hoạt bằng cách chờ PendSV Ngoại lệ hệ thống của ARM
- xPortSysTickHandler() : Điều này thực hiện quản lý RTOS Tick. Được kích hoạt định kỳ bởi bộ đếm thời gian Systick của bộ xử lý ARM Cortex Mx

### 5. API vTaskStartScheduler()
``` C
void xTaskStartScheduler(void);
```
- Điều này được triển khai trong tasks.c của hạt nhân(Kernel) FreeRTOS và được sử dụng để khởi động trình lập lịch RTOS.
- Hãy nhớ rằng sau khi gọi hàm này, chỉ có mã trình lập lịch được khởi tạo và tất cả các Arch. Các ngắt cụ thể sẽ được kích hoạt.
- Hàm này cũng tạo tác vụ daemon nhàn rỗi và Timer
- xTaskStartScheduler() gọi đến xPortStartScheduler() để thực hiện Arch. Các khởi tạo cụ thể như : \
\- Cấu hình bộ đếm thời gian SysTick để phát hành các ngắt ở tốc độ mong muốn (như được cấu hình trong mục cấu hình configTICK_RATE_HZ trong FreeRTOSConfig.h) \
\- Cấu hình mức độ ưu tiên cho các ngắt PendSV và Systick. \
\- Bắt đầu tác vụ đầu tiên bằng cách thực thi lệnh SVC
- Về cơ bản, hàm này kích hoạt trình lập lịch (tức là nhiều ngắt cụ thể của Arch hay còn gọi là ngắt hạt nhân) và không bao giờ trả về.

## VII. FreeRTOS Kernel interrupts và Scheduling of tasks
1. FreeRTOS Kernel interrupts 
- Khi FreeRTOS chạy trên MCU dựa trên Bộ xử lý ARM Cortex Mx, các ngắt dưới đây được sử dụng để triển khai Lên lịch tác vụ.\
\- Ngắt SVC (trình xử lý SVC sẽ được sử dụng để khởi chạy Tác vụ đầu tiên) \
\- Ngắt PendSV (trình xử lý PendSV được sử dụng để thực hiện chuyển đổi ngữ cảnh giữa các tác vụ) \
\- Ngắt SysTick (Trình xử lý SysTick triển khai Quản lý Tick RTOS)
- ``note`` \ 
\- Nếu ngắt SysTick được sử dụng cho mục đích khác trong ứng dụng thì có thể sử dụng bất kỳ thiết bị ngoại vi bộ đếm thời gian nào khác có sẵn
\- Tất cả các ngắt được định cấu hình ở mức ưu tiên ngắt thấp nhất có thể.

## VIII. RTOS Tick
### 1. RTOS Tick
![image](./img/RTOS_Tick.png)
- RTOS Ticking được thực hiện bằng cách sử dụng phần cứng hẹn giờ của MCU (SysTick Timer)
- RTOS Tick dùng để theo dõi thời gian đã trôi qua
- Thay đổi RTOS Tick bằng cách cấu hình configTICK_RATE_HZ trong FreeRTOSConfig.h
- Biến toàn cục xTickCount, và nó được tăng lên một bất cứ khi nào ngắt tích tắc xảy ra

- RTOS Tick Được sử dụng để chuyển đổi ngữ cảnh sang Nhiệm vụ tiềm năng tiếp theo \
\- ISR tích tắc chạy
\- Tất cả các nhiệm vụ trạng thái sẵn sàng được quét
\- Xác định nhiệm vụ tiềm năng tiếp theo sẽ chạy
\- Nếu tìm thấy, kích hoạt chuyển đổi ngữ cảnh bằng cách đang chờ ngắt PendSV
\- Trình xử lý PendSV đảm nhiệm việc chuyển đổi ra khỏi nhiệm vụ cũ và chuyển đổi vào nhiệm vụ mới
### 2. Cấu hình RTOS tick timer (SysTick)
![imgae](./img/Config_RTOS_Tick_Timer.png)
- `` Ví dụ `` \
\- Nếu configCPU_CLK_HZ = 16000000 + configTICK_RATE_HZ = 1000Hz. => portSYSTICK_NVIC_LOAD_REG = (configCPU_CLK_HZ/configTICK_RATE_HZ) -1 = 15999 \
\- khi bộ đếm(Timer) đếm đến 15999->0 ngắt được tạo ra. Thời gian sảy ra ngắt 1ms
## IX. Context Switching 
### 1. Context Switching
- Chuyển đổi ngữ cảnh là quá trình chuyển đổi ra khỏi một tác vụ và chuyển đổi vào một tác vụ khác trên CPU để thực thi.
- Trong RTOS, Chuyển đổi ngữ cảnh được xử lý bởi Trình lập lịch.
- Trong FreeRTOS, Chuyển đổi ngữ cảnh được xử lý bởi PendSV Handler tìm trong port.c
- Nếu trình lập lịch là trình lập lịch ưu tiên dựa trên mức độ ưu tiên, thì đối với mỗi lần ngắt RTOS, trình lập lịch sẽ so sánh mức độ ưu tiên của tác vụ đang chạy với mức độ ưu tiên của danh sách các tác vụ đã sẵn sàng. Nếu có bất kỳ tác vụ đã sẵn sàng nào có mức độ ưu tiên cao hơn tác vụ đang chạy thì chuyển đổi ngữ cảnh sẽ xảy ra.
- Trên FreeRTOS, bạn cũng có thể kích hoạt chuyển đổi ngữ cảnh theo cách thủ công bằng cách sử dụng macro taskYIELD()
- Chuyển đổi ngữ cảnh cũng xảy ra ngay lập tức bất cứ khi nào tác vụ mới bỏ chặn và nếu mức độ ưu tiên của nó cao hơn tác vụ đang chạy hiện tại.
### 2. Task State 
Khi một tác vụ thực thi trên Bộ xử lý, nó sử dụng
- Các thanh ghi lõi của Bộ xử lý.
- Nếu một Tác vụ muốn thực hiện bất kỳ thao tác đẩy và bật nào (trong khi gọi hàm) thì nó sử dụng bộ nhớ ngăn xếp chuyên dụng của riêng nó \
![image](./img/Task_State.png)
### 3. ARM Cortex Mx Core registers 
![image](./img/core_reg.png)
### 4. Stacks 
![image](./img/RAM.png)
- Có chủ yếu 2 Stack Memories khác nhau trong thời gian chạy của ứng dụng dựa trên FreeRTOS
### 5. Task Creation
![image](./img/Task_Create_mem.png)
- TCB sẽ được khởi tạo trong RAM(Heap section)
- Bộ nhớ Stack chuyên dụng sẽ được khởi tạo cho một tác vụ. Bộ nhớ stack này sẽ được theo dõi bằng thanh ghi PSP.
- Task sẽ được đưa vào danh sách Sẵn sàng để người lập lịch chọn

### 6. Context Switching with animation
![image](./img/Context_Switch_Animation.png)
#### Task switching out procedure 
Trước khi tác vụ được chuyển đổi, cần lưu ý những điều sau.
- Các thanh ghi lõi bộ xử lý R0, R1, R2, R3, R12, LR, PC, xPSR (khung ngăn xếp) được lưu tự động vào ngăn xếp riêng của tác vụ bởi trình tự nhập ngắt SysTick của bộ xử lý.
- Nếu cần Chuyển đổi ngữ cảnh thì bộ đếm thời gian SysTick sẽ chờ Ngoại lệ PendSV và trình xử lý PendSV chạy
- Các thanh ghi lõi bộ xử lý (R4-R11, R14) phải được lưu thủ công vào bộ nhớ ngăn xếp riêng của tác vụ (Lưu ngữ cảnh)
- Lưu giá trị đầu ngăn xếp mới (PSP) vào thành viên đầu tiên của TCB
- Chọn Nhiệm vụ tiềm năng tiếp theo để thực thi trên CPU. Được chăm sóc bởi vTaskSwitchContext() được triển khai trong tasks.c
1. Exception Entry 
![image](./img/Exception_Entry.png)
2. PendSV Handler Entry
![image](./img/PendSV_Handler_Entry%20.png)
3. Save core registers 
![image](./img/Save_core_registers.png)
4. Save PSP Into TCB 
![image](./img/Save_PSP_Into_TCB.png)

#### Task Switching In Procedure
Vì vậy, tại thời điểm này, chúng ta đã biết tác vụ nào (TCB) nên được
chuyển đổi trong. Điều đó có nghĩa là TCB của tác vụ có thể chuyển đổi mới có thể được truy cập
bởi pxCurrentTCB
- Trước tiên, hãy lấy địa chỉ của đỉnh ngăn xếp. Sao chép giá trị của
pxTopOfStack vào thanh ghi PSP
- Đưa tất cả các thanh ghi (R4-R11, R14) (Khôi phục ngữ cảnh)
- Thoát ngoại lệ: Bây giờ PSP đang trỏ đến địa chỉ bắt đầu của
khung ngăn xếp sẽ tự động được đưa ra do
thoát ngoại lệ

1. Load PSP 
![image](./img/Load_PSP.png)
2. POP all Core Registers
![image](./img/POP_all_Core_Registers.png)
3. Exception Exit 
![image](./img/Exception_Exit.png)


