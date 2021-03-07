package mooc.vandy.java4android.buildings.logic;

/**
 * This is the House class file that extends Building.
 */
public class House extends Building {
    private String mOwner;
    private boolean mPool;

    public House(int length, int width, int lotLength, int lotWidth) {
        super(length, width, lotLength, lotWidth);
        mOwner = null;
        mPool = false;
    }

    public House(int length, int width, int lotLength, int lotWidth, String owner) {
        this(length, width, lotLength, lotWidth);
        mOwner = owner;
    }

    public House(int length, int width, int lotLength, int lotWidth, String owner, boolean pool) {
        this(length, width, lotLength, lotWidth, owner);
        mPool = pool;
    }

    public String getOwner(){
        return mOwner;
    }

    public boolean hasPool() {
        return mPool;
    }

    public void setOwner(String mOwner) {
        this.mOwner = mOwner;
    }

    public void setPool(boolean pool) {
        this.mPool = pool;
    }

    public String toString() {
        String ans = "";

        if (mOwner != null) {
            ans += mOwner;
        }
        else {
            ans += "n/a";
        }

        if (mPool) {
            ans += "; has a pool";
        }

        if (this.calcLotArea() > this.calcBuildingArea()) {
            ans += "; has a big open space";
        }

        return ("Owner: " + ans);
    }

    public boolean equals(Object other) {
        if (other instanceof House) {
            House house = (House) other;

            if (this.hasPool() == house.hasPool() && this.calcBuildingArea() == house.calcBuildingArea())
                return true;
        }
        return false;
    }
}
