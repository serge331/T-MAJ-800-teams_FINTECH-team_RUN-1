<?php

namespace Domain\Accidents\Models;

use Database\Factories\AccidentFactory;
use Illuminate\Database\Eloquent\Builder;
use Illuminate\Database\Eloquent\Factories\HasFactory;
use Illuminate\Database\Eloquent\Model;
use Illuminate\Support\Carbon;
use MatanYadaev\EloquentSpatial\Objects\Point;
use MatanYadaev\EloquentSpatial\SpatialBuilder;

/**
 * @mixin Builder
 *
 * @method static Builder|static query()
 * @method static static make(array $attributes = [])
 * @method static static create(array $attributes = [])
 * @method Accident firstOrNew(array $attributes = [], array $values = [])
 * @method Accident firstOrFail($columns = ['*'])
 * @method Accident firstOrCreate(array $attributes, array $values = [])
 * @method Accident updateOrCreate(array $attributes, array $values = [])
 * @method null|static first($columns = ['*'])
 * @method static static findOrFail($id, $columns = ['*'])
 * @method static static findOrNew($id, $columns = ['*'])
 * @method static null|static find($id, $columns = ['*'])
 *
 * @property-read int $id
 *
 * @property string $location
 * @property Carbon $date
 * @property string $description
 * @property int $casualties
 * @property string|null $liability
 * @property array $speed_samples
 * @property array $rainfall_samples
 *
 * @property-read Carbon $created_at
 * @property-read Carbon $updated_at
 */
class Accident extends Model
{
    use HasFactory;

    protected $table = 'accidents';

    protected $fillable = [
        'location',
        'date',
        'description',
        'casualties',
        'liability',
        'speed_samples',
        'rainfall_samples',
    ];

    protected $casts = [
//        'location' => Point::class,
        'casualties' => 'integer',
        'speed_samples' => 'array',
        'rainfall_samples' => 'array',
    ];

    protected static function newFactory(): AccidentFactory
    {
        return AccidentFactory::new();
    }
}
