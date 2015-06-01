package vn.edu.fpt.mob;

import android.bluetooth.BluetoothDevice;
import android.os.ParcelUuid;

import java.util.ArrayList;

import vn.edu.fpt.mob.bluetooth.BluetoothUtils;

/**
 * Created by Huy on 6/1/2015.
 */
public class DeviceData {
    private String name = "";
    private String address = "";
    private int bondState = BluetoothDevice.BOND_NONE;
    private ArrayList<ParcelUuid> uuids = null;
    private final int deviceClass;
    private final int majorDeviceClass;

    public DeviceData(BluetoothDevice device, String emptyName) {
        name = device.getName();
        address = device.getAddress();
        bondState = device.getBondState();

        if (name == null || name.isEmpty()) name = emptyName;
        deviceClass = device.getBluetoothClass().getDeviceClass();
        majorDeviceClass = device.getBluetoothClass().getMajorDeviceClass();
        uuids = BluetoothUtils.getDeviceUuids(device);
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getAddress() {
        return address;
    }

    public void setAddress(String address) {
        this.address = address;
    }

    public int getBondState() {
        return bondState;
    }

    public void setBondState(int bondState) {
        this.bondState = bondState;
    }

    public ArrayList<ParcelUuid> getUuids() {
        return uuids;
    }

    public void setUuids(ArrayList<ParcelUuid> uuids) {
        this.uuids = uuids;
    }

    public int getDeviceClass() {
        return deviceClass;
    }

    public int getMajorDeviceClass() {
        return majorDeviceClass;
    }
}
