#pragma once
#pragma region GamemodeTextures
class GamemodeTexture {
public:
	static const GamemodeTexture Adversary10;
	static const GamemodeTexture Adversary12;
	static const GamemodeTexture Adversary16;
	static const GamemodeTexture Adversary4;
	static const GamemodeTexture Adversary8;
	static const GamemodeTexture AdversaryBunker;
	static const GamemodeTexture AdversaryIcon;
	static const GamemodeTexture AircraftCarrier;
	static const GamemodeTexture AirRaceIcon;
	static const GamemodeTexture ArenaPremium;
	static const GamemodeTexture ArenaSeries;
	static const GamemodeTexture ArmWrestlingIcon;
	static const GamemodeTexture BasejumpIcon;
	static const GamemodeTexture BikeRaceIcon;
	static const GamemodeTexture BikeTimeTrails;
	static const GamemodeTexture CaptureTheFlagIcon;
	static const GamemodeTexture CayoPericoAttrition;
	static const GamemodeTexture CayoPericoIcon;
	static const GamemodeTexture ChallengeSeries;
	static const GamemodeTexture CommunitySeriesIcon;
	static const GamemodeTexture CoronaMarker;
	static const GamemodeTexture CoronaPoint;
	static const GamemodeTexture CoronaShade;
	static const GamemodeTexture CustomIcon;
	static const GamemodeTexture DartsIcon;
	static const GamemodeTexture DeathmatchMarker256;
	static const GamemodeTexture DragRace;
	static const GamemodeTexture DriftRace;
	static const GamemodeTexture FeaturedSeries;
	static const GamemodeTexture FootRaceIcon;
	static const GamemodeTexture GangattackIcon;
	static const GamemodeTexture GolfIcon;
	static const GamemodeTexture HotringCircuit;
	static const GamemodeTexture HswRaceSeries;
	static const GamemodeTexture HswTimeTrial;
	static const GamemodeTexture KingOfTheHill;
	static const GamemodeTexture KingOfTheHillTeams;
	static const GamemodeTexture LandRaceIcon;
	static const GamemodeTexture LastTeamStandingIcon;
	static const GamemodeTexture OffRoadRaceIcon;
	static const GamemodeTexture OpenWheelRace;
	static const GamemodeTexture PilotSchoolIcon;
	static const GamemodeTexture PursuitSeries;
	static const GamemodeTexture RcTimeTrials;
	static const GamemodeTexture SeaRaceIcon;
	static const GamemodeTexture ShootingRangeIcon;
	static const GamemodeTexture SpecialVehicleRaceSeries;
	static const GamemodeTexture StreetRaceSeries;
	static const GamemodeTexture StuntIcon;
	static const GamemodeTexture StuntModeIcon;
	static const GamemodeTexture StuntPremiumIcon;
	static const GamemodeTexture SurvivalIcon;
	static const GamemodeTexture TargetRace;
	static const GamemodeTexture TeamdeathmatchIcon;
	static const GamemodeTexture TennisIcon;
	static const GamemodeTexture TimetrialIcon;
	static const GamemodeTexture TransformRaceIcon;
	static const GamemodeTexture VehicledeathmatchIcon;
	static const GamemodeTexture YanktonSurvival;

	constexpr const char* GetName() const { return m_Name; }

	bool operator==(const GamemodeTexture& other) const { return m_Name == other.m_Name; }

private:
	constexpr explicit GamemodeTexture(const char* name) : m_Name(name) {}
	const char* m_Name;
};

inline const GamemodeTexture GamemodeTexture::Adversary10("adversary_10");
inline const GamemodeTexture GamemodeTexture::Adversary12("adversary_12");
inline const GamemodeTexture GamemodeTexture::Adversary16("adversary_16");
inline const GamemodeTexture GamemodeTexture::Adversary4("adversary_4");
inline const GamemodeTexture GamemodeTexture::Adversary8("adversary_8");
inline const GamemodeTexture GamemodeTexture::AdversaryBunker("adversary_bunker");
inline const GamemodeTexture GamemodeTexture::AdversaryIcon("adversary_icon");
inline const GamemodeTexture GamemodeTexture::AircraftCarrier("aircraft_carrier");
inline const GamemodeTexture GamemodeTexture::AirRaceIcon("air_race_icon");
inline const GamemodeTexture GamemodeTexture::ArenaPremium("arena_premium");
inline const GamemodeTexture GamemodeTexture::ArenaSeries("arena_series");
inline const GamemodeTexture GamemodeTexture::ArmWrestlingIcon("arm_wrestling_icon");
inline const GamemodeTexture GamemodeTexture::BasejumpIcon("basejump_icon");
inline const GamemodeTexture GamemodeTexture::BikeRaceIcon("bike_race_icon");
inline const GamemodeTexture GamemodeTexture::BikeTimeTrails("bike_time_trails");
inline const GamemodeTexture GamemodeTexture::CaptureTheFlagIcon("capture_the_flag_icon");
inline const GamemodeTexture GamemodeTexture::CayoPericoAttrition("cayo_perico_attrition");
inline const GamemodeTexture GamemodeTexture::CayoPericoIcon("cayo_perico_icon");
inline const GamemodeTexture GamemodeTexture::ChallengeSeries("challenge_series");
inline const GamemodeTexture GamemodeTexture::CommunitySeriesIcon("community_series_icon");
inline const GamemodeTexture GamemodeTexture::CoronaMarker("corona_marker");
inline const GamemodeTexture GamemodeTexture::CoronaPoint("corona_point");
inline const GamemodeTexture GamemodeTexture::CoronaShade("corona_shade");
inline const GamemodeTexture GamemodeTexture::CustomIcon("custom_icon");
inline const GamemodeTexture GamemodeTexture::DartsIcon("darts_icon");
inline const GamemodeTexture GamemodeTexture::DeathmatchMarker256("deathmatch_marker_256");
inline const GamemodeTexture GamemodeTexture::DragRace("drag_race");
inline const GamemodeTexture GamemodeTexture::DriftRace("drift_race");
inline const GamemodeTexture GamemodeTexture::FeaturedSeries("featured_series");
inline const GamemodeTexture GamemodeTexture::FootRaceIcon("foot_race_icon");
inline const GamemodeTexture GamemodeTexture::GangattackIcon("gangattack_icon");
inline const GamemodeTexture GamemodeTexture::GolfIcon("golf_icon");
inline const GamemodeTexture GamemodeTexture::HotringCircuit("hotring_circuit");
inline const GamemodeTexture GamemodeTexture::HswRaceSeries("hsw_race_series");
inline const GamemodeTexture GamemodeTexture::HswTimeTrial("hsw_time_trial");
inline const GamemodeTexture GamemodeTexture::KingOfTheHill("king_of_the_hill");
inline const GamemodeTexture GamemodeTexture::KingOfTheHillTeams("king_of_the_hill_teams");
inline const GamemodeTexture GamemodeTexture::LandRaceIcon("land_race_icon");
inline const GamemodeTexture GamemodeTexture::LastTeamStandingIcon("last_team_standing_icon");
inline const GamemodeTexture GamemodeTexture::OffRoadRaceIcon("off_road_race_icon");
inline const GamemodeTexture GamemodeTexture::OpenWheelRace("open_wheel_race");
inline const GamemodeTexture GamemodeTexture::PilotSchoolIcon("pilot_school_icon");
inline const GamemodeTexture GamemodeTexture::PursuitSeries("pursuit_series");
inline const GamemodeTexture GamemodeTexture::RcTimeTrials("rc_time_trials");
inline const GamemodeTexture GamemodeTexture::SeaRaceIcon("sea_race_icon");
inline const GamemodeTexture GamemodeTexture::ShootingRangeIcon("shooting_range_icon");
inline const GamemodeTexture GamemodeTexture::SpecialVehicleRaceSeries("special_vehicle_race_series");
inline const GamemodeTexture GamemodeTexture::StreetRaceSeries("street_race_series");
inline const GamemodeTexture GamemodeTexture::StuntIcon("stunt_icon");
inline const GamemodeTexture GamemodeTexture::StuntModeIcon("stunt_mode_icon");
inline const GamemodeTexture GamemodeTexture::StuntPremiumIcon("stunt_premium_icon");
inline const GamemodeTexture GamemodeTexture::SurvivalIcon("survival_icon");
inline const GamemodeTexture GamemodeTexture::TargetRace("target_race");
inline const GamemodeTexture GamemodeTexture::TeamdeathmatchIcon("teamdeathmatch_icon");
inline const GamemodeTexture GamemodeTexture::TennisIcon("tennis_icon");
inline const GamemodeTexture GamemodeTexture::TimetrialIcon("timetrial_icon");
inline const GamemodeTexture GamemodeTexture::TransformRaceIcon("transform_race_icon");
inline const GamemodeTexture GamemodeTexture::VehicledeathmatchIcon("vehicledeathmatch_icon");
inline const GamemodeTexture GamemodeTexture::YanktonSurvival("yankton_survival");
#pragma endregion