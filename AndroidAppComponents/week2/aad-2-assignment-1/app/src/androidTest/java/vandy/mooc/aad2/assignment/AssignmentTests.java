package vandy.mooc.aad2.assignment;


import android.view.View;
import android.view.ViewGroup;
import android.view.ViewParent;

import androidx.test.core.app.ApplicationProvider;
import androidx.test.espresso.ViewInteraction;
import androidx.test.ext.junit.runners.AndroidJUnit4;
import androidx.test.filters.LargeTest;
import androidx.test.rule.ActivityTestRule;
import androidx.test.rule.GrantPermissionRule;

import org.hamcrest.Description;
import org.hamcrest.Matcher;
import org.hamcrest.TypeSafeMatcher;
import org.junit.Rule;
import org.junit.Test;
import org.junit.runner.RunWith;

import vandy.mooc.aad2.assignment.activities.MainActivity;
import vandy.mooc.aad2.framework.utils.CacheUtils;
import vandy.mooc.aad2.framework.utils.FileUtils;

import static android.content.Context.MODE_PRIVATE;
import static androidx.test.espresso.Espresso.onView;
import static androidx.test.espresso.action.ViewActions.click;
import static androidx.test.espresso.assertion.ViewAssertions.matches;
import static androidx.test.espresso.matcher.ViewMatchers.hasDescendant;
import static androidx.test.espresso.matcher.ViewMatchers.isDisplayed;
import static androidx.test.espresso.matcher.ViewMatchers.withContentDescription;
import static androidx.test.espresso.matcher.ViewMatchers.withId;
import static androidx.test.espresso.matcher.ViewMatchers.withText;
import static org.hamcrest.Matchers.allOf;

@LargeTest
@RunWith(AndroidJUnit4.class)
public class AssignmentTests {
    /**
     * This is a list of the default URLs to be downloaded.
     */
    private final static String[] defaultURLs = {
            "https://upload.wikimedia.org/wikipedia/en/0/09/DataTNG.jpg",
            "https://www.dre.vanderbilt.edu/~schmidt/gifs/dougs-xsmall.jpg",
            "https://2.bp.blogspot.com/-c2U3HUQZVy8/UV7KI2bodLI/AAAAAAAAA4g/DJEEmv-FmNY/s1600" +
                    "/galaxy_universe-normal.jpg",
    };

    @Rule
    public ActivityTestRule<MainActivity> mActivityTestRule =
            new ActivityTestRule<MainActivity>(MainActivity.class) {
                @Override
                protected void beforeActivityLaunched() {
                    // Clear shared preferences.
                    ApplicationProvider.getApplicationContext()
                            .getSharedPreferences(null, MODE_PRIVATE)
                            .edit()
                            .clear()
                            .commit();

                    // Clear the image cache.
                    FileUtils.deleteDirectory(
                            ApplicationProvider.getApplicationContext(),
                            FileUtils.getImageDirectory());
                    CacheUtils.clearCache(ApplicationProvider.getApplicationContext());
                }
            };

    @Rule
    public GrantPermissionRule mGrantPermissionRule =
            GrantPermissionRule.grant(
                    "android.permission.READ_EXTERNAL_STORAGE",
                    "android.permission.WRITE_EXTERNAL_STORAGE");
    /**
     * Full application test that starts the application and attempts to
     * download a mal-formed URL.
     * <p/>
     * NOTE: THIS TEST REQUIRES AN ACTIVE INTERNET CONNECTION.
     */
    @Rubric(
            value = "fullAppDownloadAMissingUrlResourceTest",
            goal = "The goal of this evaluation is to test " +
                    "if the application responds with the correct Toast when " +
                    "the user attempts to download a missing URL resource",
            points = 1.0,
            reference = "This Test fails when: DownloadActivity fail to show " +
                    "the expected Toast message when user attempts to " +
                    "download a malformed image URL."
    )
    @Test
    public void mainActivityTest() {
        ViewInteraction overflowMenuButton = onView(
                allOf(withContentDescription("More options"),
                        childAtPosition(
                                childAtPosition(
                                        withId(R.id.toolbar),
                                        1),
                                0),
                        isDisplayed()));
        overflowMenuButton.perform(click());

        ViewInteraction appCompatTextView = onView(
                allOf(withId(R.id.title), withText("Load Defaults"),
                        childAtPosition(
                                childAtPosition(
                                        withId(R.id.content),
                                        0),
                                0),
                        isDisplayed()));
        appCompatTextView.perform(click());

        ViewInteraction floatingActionButton = onView(
                allOf(withId(R.id.download_fab),
                        childAtPosition(
                                childAtPosition(
                                        withId(android.R.id.content),
                                        0),
                                4),
                        isDisplayed()));
        floatingActionButton.perform(click());

        // Check for expected images.
        for (String urlToCheck : defaultURLs) {
            onView(withId(R.id.recycler_view_fragment))
                    .check(matches(hasDescendant(withContentDescription(urlToCheck))));
        }
    }

    private static Matcher<View> childAtPosition(
            final Matcher<View> parentMatcher, final int position) {

        return new TypeSafeMatcher<View>() {
            @Override
            public void describeTo(Description description) {
                description.appendText("Child at position " + position + " in parent ");
                parentMatcher.describeTo(description);
            }

            @Override
            public boolean matchesSafely(View view) {
                ViewParent parent = view.getParent();
                return parent instanceof ViewGroup && parentMatcher.matches(parent)
                        && view.equals(((ViewGroup) parent).getChildAt(position));
            }
        };
    }
}
