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
    Channel.SCS_TELEMETRY_TRUCK_CHANNEL_speed,
    SCSValueType.TYPE_float
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
    Channel.SCS_TELEMETRY_TRUCK_CHANNEL_engine_rpm,
    SCSValueType.TYPE_float
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
    Channel.SCS_TELEMETRY_CHANNEL_game_time,
    SCSValueType.TYPE_u32
);

if (result != Result.SUCCESS)
{
    return;
}

while (connection.Dispatch()) ;
