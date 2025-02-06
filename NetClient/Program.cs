using TruckConnect;

using Connection connection = new("\\\\.\\pipe\\managedtruckconnect");
float speed = 0, rpm = 0;
UInt32 minutes = 0;

Action print = () =>
{
    Console.WriteLine($"{minutes} Minutes | {speed} m/s, {rpm} rpm");
};

Result result;
result = connection.Register(
    (Registration registration, byte[] bytes) =>
    {
        speed = BitConverter.ToSingle(bytes);
        print();
    },
    38,
    5
);

if (result != Result.SUCCESS)
{
    return;
}

result = connection.Register(
    (Registration registration, byte[] bytes) =>
    {
        rpm = BitConverter.ToSingle(bytes);
        print();
    },
    39,
    5
);

if (result != Result.SUCCESS)
{
    return;
}

int count = 0;
result = connection.Register(
    (Registration registration, byte[] bytes) =>
    {
        count++;
        minutes = BitConverter.ToUInt32(bytes);
        print();
        if (count == 3)
        {
            connection.Disconnect();
        }
    },
    1,
    3
);

if (result != Result.SUCCESS)
{
    return;
}

while (connection.Dispatch()) ;
