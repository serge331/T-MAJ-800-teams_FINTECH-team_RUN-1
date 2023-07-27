<?php

namespace Database\Factories;

use Domain\Accidents\Models\Accident;
use Illuminate\Database\Eloquent\Factories\Factory;
use Illuminate\Support\Facades\Hash;
use Illuminate\Support\Str;
use MatanYadaev\EloquentSpatial\Objects\Point;

/**
 * @extends Factory<Accident>
 */
class AccidentFactory extends Factory
{
    /**
     * The name of the factory's corresponding model.
     *
     * @var string
     */
    protected $model = Accident::class;

    /**
     * Define the model's default state.
     *
     * @return array<string, mixed>
     */
    public function definition(): array
    {
        return [
            'location' => $this->faker->city(),
            'date' => $this->faker->dateTime(),
            'description' => $this->faker->text(),
            'casualties' => $this->faker->numberBetween(1, 10),
            'speed_samples' => array(
                0 => ['speed' => 50],
                1 => ['speed' => 60],
                2 => ['speed' => 70],
                3 => ['speed' => 80],
                4 => ['speed' => 90],
            ),
            'rainfall_samples' => array(
                0 => ['rainfall' => 0],
                1 => ['rainfall' => 0],
                2 => ['rainfall' => 0],
                3 => ['rainfall' => 0],
                4 => ['rainfall' => 0],
            ),
        ];
    }
}
