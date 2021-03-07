package mooc.vandy.java4android.buildings.logic;

/**
 * This is the office class file, it is a subclass of Building.
 */
public class Office extends Building {
    private String mBusinessName;
    private int mParkingSpaces;
    private static int sTotalOffices = 0;

    public Office(int length, int width, int lotLength, int lotWidth) {
        super(length, width, lotLength, lotWidth);
        mBusinessName = null;
        mParkingSpaces = 0;
        sTotalOffices++;
    }

    public Office(int length, int width, int lotLength, int lotWidth, String businessName) {
        this(length, width, lotLength, lotWidth);
        mBusinessName = businessName;
    }

    public Office(int length, int width, int lotLength, int lotWidth, String businessName, int parkingSpaces) {
        this(length, width, lotLength, lotWidth, businessName);
        mParkingSpaces = parkingSpaces;
    }

    public String getBusinessName() {
        return mBusinessName;
    }

    public int getParkingSpaces() {
        return mParkingSpaces;
    }

    public static int getTotalOffices() {
        return sTotalOffices;
    }

    public void setBusinessName(String businessName) {
        mBusinessName = businessName;
    }

    public void setParkingSpaces(int parkingSpaces) {
        mParkingSpaces = parkingSpaces;
    }

    public String toString() {
        String ans = "";

        if (mBusinessName != null) {
            ans += mBusinessName;
        }
        else {
            ans += "unoccupied";
        }

        if (mParkingSpaces != 0) {
            ans += ("; has " + mParkingSpaces + " parking spaces");
        }

        return ("Business: " + ans + " (total offices: " + sTotalOffices + ")");
    }

    public boolean equals(Object other) {
        if (other instanceof Office) {
            Office office = (Office) other;
            return (this.calcBuildingArea() == office.calcBuildingArea() && this.mParkingSpaces == office.getParkingSpaces());
        }

        return false;
    }
}
